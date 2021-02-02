#include "sharon_pch.h"
#include "Application.h"

#include "Input.h"
#include "Renderer/Renderer.h"

namespace Sharon
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        SHARON_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);

        // // // // // // // // // // // // // // // // // // // // // // // // // // // //

        m_SqVA.reset(VertexArray::Create());

        float vertices[4 * 3] = {
             0.5f,  0.5f, 0.0f,  // top right
            -0.5f, -0.5f, 0.0f,  // bottom left
             0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f,  0.5f, 0.0f   // top left 
        };
        std::shared_ptr<VertexBuffer> SqVB;
        SqVB.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
        SqVB->SetLayout({
            { ShaderDataType::Float3, "a_Position"},
        });
        m_SqVA->AddVertexBuffer(SqVB);

        unsigned int indices[6] = {
            0, 2, 3,   // first triangle
            1, 2, 3    // second triangle
        };
        std::shared_ptr<IndexBuffer> SqIB;
        SqIB.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_SqVA->SetIndexBuffer(SqIB);
            
        std::string vertexShader = R"(
            #version 330 core
            layout(location = 0) in vec3 a_Posision;
                                                                                                         
            out vec2 fragCoord;

            void main()
            {
                gl_Position = vec4(a_Posision, 1.0); 
                fragCoord = vec2(gl_Position * 0.5 + 0.5);
            }
        )";

        std::string fragmentShader = R"(
            #version 330 core
            out vec4 fragColor;
                                                                                                         
            in vec2 fragCoord;
                                                                                                        
            void main()
            {
                fragColor = vec4(fragCoord.xy, 0.4f, 1.0f);
            }
        )";

        m_Shader.reset(new Shader(vertexShader, fragmentShader));
    }

    Application::~Application()
    {

    }

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* layer)
    {
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowClosedEvent>(BIND_EVENT_FN(OnWindowClose)); // lambda?

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
        {
            (*--it)->OnEvent(e);
            if (e.Handled)
                break;
        }
    }

    void Application::Run()
    {
        while (m_Running)
        {
            RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
            RenderCommand::Clear();

            Renderer::BeginScene();

            m_Shader->Bind();
            Renderer::Sumbit(m_SqVA);

            Renderer::EndScene();
            //////////////////////////////////
            for (Layer* layer : m_LayerStack)
                layer->OnUpdate();

            m_ImGuiLayer->Begin();
            for (Layer* layer : m_LayerStack)
                layer->OnImGuiRender();
            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindowClose(WindowClosedEvent& e)
    {
        m_Running = false;
        return true;
    }
}