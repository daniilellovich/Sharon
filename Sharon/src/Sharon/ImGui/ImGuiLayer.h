#pragma once
#include "Sharon/Layer.h"

#include "Sharon/Events/ApplicationEvent.h"
#include "Sharon/Events/KeyEvent.h"
#include "Sharon/Events/MouseEvent.h"

namespace Sharon
{
    class SHARON_API ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();
        
        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnImGuiRender() override;

        void Begin();
        void End();

    private:
        float m_Time = 0.0f ;
    };
}
