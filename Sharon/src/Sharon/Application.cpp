#include "sharon_pch.h"
#include "Application.h"

namespace Sharon
{

    Application::Application()
    {

    }

    Application::~Application()
    {

    }

    void Application::Run()
    {
        SHARON_CORE_TRACE("Hi, I am Sharon!");
        SHARON_INFO("Hello, I am the app.");
        while (true);
    }
}