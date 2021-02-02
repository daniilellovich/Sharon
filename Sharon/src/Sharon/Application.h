#pragma once
#include "Core.h"

#include "Window.h"
#include "LayerStack.h"
#include "Events/ApplicationEvent.h"

#include "Sharon/ImGui/ImGuiLayer.h"

#include "Renderer/Shader.h" // temp
#include "Renderer/VertexArray.h"
#include "Renderer/Buffer.h"

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

        inline Window& GetWindow() { return *m_Window; }
    
        inline static Application& Get() { return *s_Instance; }

    private:
        bool OnWindowClose(WindowClosedEvent& e);

        std::unique_ptr<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer;
        bool m_Running = true;
        LayerStack m_LayerStack;

        // temp
        std::shared_ptr<Shader> m_Shader;
        std::shared_ptr<VertexArray> m_SqVA;
    private:
        static Application* s_Instance;
    };

    // to be defined in a CLIENT
    Application* CreateApplication();
}