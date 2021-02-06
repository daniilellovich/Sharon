#include "imgui/imgui.h"
#include "Sharon.h"
#include <glm/glm/ext/matrix_transform.hpp>

class ExampleLayer : public Sharon::Layer
{
public:
    ExampleLayer()
        : Layer("Example layer1"), m_OrthCamera({ -1.6f, 1.6f, -0.9f, 0.9f }), m_CameraPos(0.0f), m_ModelPos(0.0f)
    {
        m_SqVA.reset(Sharon::VertexArray::Create());

        float vertices[4 * 3] = {
             0.5f,  0.5f, 0.0f,      // top right
            -0.5f, -0.5f, 0.0f,      // bottom left
             0.5f, -0.5f, 0.0f,      // bottom right
            -0.5f,  0.5f, 0.0f       // top left 
        };
        std::shared_ptr<Sharon::VertexBuffer> SqVB;
        SqVB.reset(Sharon::VertexBuffer::Create(vertices, sizeof(vertices)));
        SqVB->SetLayout({
            { Sharon::ShaderDataType::Float3, "a_Position"},
            });
        m_SqVA->AddVertexBuffer(SqVB);

        unsigned int indices[6] = {
            0, 2, 3,                 // first triangle
            1, 2, 3                  // second triangle
        };
        std::shared_ptr<Sharon::IndexBuffer> SqIB;
        SqIB.reset(Sharon::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_SqVA->SetIndexBuffer(SqIB);

        std::string vertexShader = R"(
            #version 330 core
            layout(location = 0) in vec3 a_Posision;
                             
            uniform mat4 u_ViewProj;
            uniform mat4 u_Model;
                                                                            
            out vec2 fragCoord;

            void main()
            {
                gl_Position = u_ViewProj * u_Model * vec4(a_Posision, 1.0); 
                fragCoord = vec2(gl_Position * 0.5 + 0.5);
            }
        )";

        std::string fragmentShader = R"(
            #version 330 core
            out vec4 fragColor;
                                                                                                         
            in vec2 fragCoord;
            uniform vec4 u_Color;
                                                                                                        
            void main()
            {
                fragColor = vec4(fragCoord.xy, 0.4f, 1.0f);
                fragColor = vec4(fragCoord, 0.0f, 1.0f);
            }
        )";

        m_Shader.reset(new Sharon::Shader(vertexShader, fragmentShader));
    }

    void OnUpdate(Sharon::TimeStep ts) override
    {
   //     SHARON_TRACE("Delta time: {0}", ts.GetSeconds());

        // camera
        if (Sharon::Input::IsKeyPressed(SHARON_KEY_LEFT))
            m_CameraPos.x -= m_CameraMoveSpeed * ts;
        else if (Sharon::Input::IsKeyPressed(SHARON_KEY_RIGHT))
            m_CameraPos.x += m_CameraMoveSpeed * ts;
        
        if (Sharon::Input::IsKeyPressed(SHARON_KEY_UP))
            m_CameraPos.y += m_CameraMoveSpeed * ts;
        else if (Sharon::Input::IsKeyPressed(SHARON_KEY_DOWN))
            m_CameraPos.y -= m_CameraMoveSpeed * ts;



        // square
        if (Sharon::Input::IsKeyPressed(SHARON_KEY_J))
            m_ModelPos.x -= m_ModelMoveSpeed * ts;
        else if (Sharon::Input::IsKeyPressed(SHARON_KEY_L))
            m_ModelPos.x += m_ModelMoveSpeed * ts;

        if (Sharon::Input::IsKeyPressed(SHARON_KEY_I))
            m_ModelPos.y += m_ModelMoveSpeed * ts;
        else if (Sharon::Input::IsKeyPressed(SHARON_KEY_K))
            m_ModelPos.y -= m_ModelMoveSpeed * ts;



        // camera rotation
        if (Sharon::Input::IsKeyPressed(SHARON_KEY_A))
            m_CameraRotation += m_CameraRotationSpeed * ts;
        else if (Sharon::Input::IsKeyPressed(SHARON_KEY_D))
            m_CameraRotation -= m_CameraRotationSpeed * ts;

        Sharon::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        Sharon::RenderCommand::Clear();

        m_OrthCamera.SetPosition(m_CameraPos);
        m_OrthCamera.SetRotation(m_CameraRotation);
            
        Sharon::Renderer::BeginScene(m_OrthCamera);

    //    Sharon::MaterialRef material = new Sharon::Material(m_Shader);
    //    material->Set("u_Color", redColor);
    //    squareMesh->SetMaterial(material);

        glm::vec4 redColor(1.0f, 0.1f, 0.1f, 1.0f);
        glm::vec4 greenColor(0.1f, 1.0f, 0.1f, 1.0f);
        glm::vec4 blueColor(0.1f, 0.1f, 1.0f, 1.0f);

        glm::mat4 model = glm::translate(glm::mat4(1.0f), m_ModelPos);
     //   m_Shader->UploadUniformFloat4("u_Color", redColor);
        Sharon::Renderer::Sumbit(m_SqVA, model, m_Shader);

        Sharon::Renderer::EndScene();
    }

    //virtual void OnImGuiRender() override
    //{
    //    ImGui::Text("My window");
    //}

    void OnEvent(Sharon::Event& event) override
    {
       // Sharon::EventDispatcher dispatcher(event);
       // dispatcher.Dispatch<Sharon::KeyPressedEvent>(SHARON_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
    }

    //bool OnKeyPressedEvent(Sharon::KeyPressedEvent& event)
    //{
    //    SHARON_TRACE(event.GetKeyCode());

    //    if (event.GetKeyCode() == SHARON_KEY_LEFT)
    //        m_CameraPos.x -= m_CameraSpeed;
    //    if (event.GetKeyCode() == SHARON_KEY_RIGHT)
    //        m_CameraPos.x += m_CameraSpeed;
    //    if (event.GetKeyCode() == SHARON_KEY_UP)
    //        m_CameraPos.y += m_CameraSpeed;
    //    if (event.GetKeyCode() == SHARON_KEY_DOWN)
    //        m_CameraPos.y -= m_CameraSpeed;

    //    return false;
    //}

    std::shared_ptr<Sharon::Shader> m_Shader;
    std::shared_ptr<Sharon::VertexArray> m_SqVA;

    Sharon::OrthographicCamera m_OrthCamera;
    glm::vec3 m_CameraPos;
    float m_CameraMoveSpeed = 2.0f;
    float m_CameraRotation = 0.0f;
    float m_CameraRotationSpeed = 60.0f;

    glm::vec3 m_ModelPos;
    float m_ModelMoveSpeed = 1.0f;

};

class Sandbox : public Sharon::Application
{
public:
    Sandbox()
    {
        PushLayer(new ExampleLayer());
    }

    ~Sandbox()
    {

    }
};

Sharon::Application* Sharon::CreateApplication()
{
    return new Sandbox();
}