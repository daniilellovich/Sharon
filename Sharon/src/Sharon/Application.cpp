#include "sharon_pch.h"
#include "Application.h"

//todo delete
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

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
        WindowResizedEvent e(1222, 44);
        SHARON_CORE_TRACE(e);
        MouseMovedEvent mve(234, 234);
        SHARON_CORE_TRACE(mve);
        KeyPressedEvent k(23, 4);
        SHARON_CORE_TRACE(k);
        MouseButtonPressedEvent rr(1);
        SHARON_CORE_TRACE(rr);

        while (true);
    }
}