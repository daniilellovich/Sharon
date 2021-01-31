#include "sharon_pch.h"
#include "Application.h"
#include "Input.h"

#include <glad/glad.h> // temp

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

        // // // //
        glGenVertexArrays(1, &m_VertexArray);
        glBindVertexArray(m_VertexArray);
        glGenBuffers(1, &m_VertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexArray);
        float vertices[4 * 3] = {
             0.5f,  0.5f, 0.0f,  // top right
            -0.5f, -0.5f, 0.0f,  // bottom left
             0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f,  0.5f, 0.0f   // top left 
        };
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

        glGenBuffers(1, &m_IndexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
        unsigned int indices[6] = {
            0, 2, 3,   // first triangle
            1, 2, 3    // second triangle
        };
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        unsigned int EBO;
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        std::string vertexShader = R"(
            #version 330 core                                                                            
            layout(location = 0) in vec3 a_Posision; // the position variable has attribute position 0         
                                                                                                         
            out vec2 fragCoord;                   
                                                                                                        
            void main()                                                                                 
            {                                                                                           
                gl_Position = vec4(a_Posision, 1.0); // see how we directly give a vec3 to vec4's constructor 
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
            glClearColor(0.1f, 0.1f, 0.1f, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            ///
            m_Shader->Bind();

            glBindVertexArray(m_VertexArray);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
            ///

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