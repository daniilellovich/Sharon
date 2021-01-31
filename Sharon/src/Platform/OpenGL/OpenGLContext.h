#pragma once

#include "Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Sharon 
{
    class SHARON_API OpenGLContext : public GraphicsContext
    {
    public:
        OpenGLContext(GLFWwindow* windowHandle);

        virtual void Init() override;
        virtual void SwapBuffers() override;
    private:
        GLFWwindow* m_WindowHandle;
    };
}