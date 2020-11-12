#pragma once
#include "Core.h"

namespace Sharon
{
    class SHARON_API Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();
    };

    // to be defined in a CLIENT
    Application* CreateApplication();
}