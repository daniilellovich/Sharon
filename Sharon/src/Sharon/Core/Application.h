#pragma once
#include "Sharon/Core/Base.h"
#include "Sharon/Core/Window.h"
#include "Sharon/Core/LayerStack.h"
#include "Sharon/Core/TimeStep.h"

#include "Sharon/Events/ApplicationEvent.h"
#include "Sharon/ImGui/ImGuiLayer.h"

namespace Sharon
{
    class SHARON_API Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();

        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);

        Window& GetWindow() { return *m_Window; }
    
        static Application& Get() { return *s_Instance; }

    private:
        bool OnWindowClose(WindowClosedEvent& e);
    
    private:
        std::unique_ptr<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer;
        bool m_Running = true;
        LayerStack m_LayerStack;
        float m_LastFrameStep = 0.0f;

    private:
        static Application* s_Instance;
    };

    // to be defined in a CLIENT
    Application* CreateApplication();
}