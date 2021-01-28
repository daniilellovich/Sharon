#pragma once
#include "sharon_pch.h"

#include "Sharon/Core.h"
#include "Sharon/Events/Event.h"

namespace Sharon
{
    struct WindowProps
    {
        std::string Title;
        unsigned int Width, Height;

        WindowProps(const std::string& title = "Sharon",
                    unsigned int width = 1200,
                    unsigned int height = 800)
            : Title(title), Width(width), Height(height) { }
    };

    // interface, should be implemented by platform-dependent window lib
    class SHARON_API Window
    {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        virtual ~Window() {}

        virtual void OnUpdate() = 0;

        virtual unsigned int GetWidth() const = 0;
        virtual unsigned int GetHeight() const = 0;

        virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const = 0;

        virtual void* GetNativeWindow() const = 0;

        static Window* Create(const WindowProps& props = WindowProps());
    };
}