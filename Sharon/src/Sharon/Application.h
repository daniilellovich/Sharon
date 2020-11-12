#pragma once
#include "Core.h"
#include "Window.h"

namespace Sharon
{
    class SHARON_API Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();

    private:
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
    };

    // to be defined in a CLIENT
    Application* CreateApplication();
}