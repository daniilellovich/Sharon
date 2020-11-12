#include <Sharon.h>

class Sandbox : public Sharon::Application
{
public:
    Sandbox()
    {

    }

    ~Sandbox()
    {

    }
};

Sharon::Application* Sharon::CreateApplication()
{
    return new Sandbox();
}