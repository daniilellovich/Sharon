#include <Sharon.h>

class ExampleLayer : public Sharon::Layer
{
public:
    ExampleLayer() 
        : Layer("Example layer1") { }

    void OnUpdate() override
    {
   //     SHARON_INFO("ExmpleLayer::Update");
    }

    void OnEvent(Sharon::Event& event) override
    {
   //     SHARON_TRACE("{0}: {1}", this->GetName(), event);
    }
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