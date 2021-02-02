#include "sharon_pch.h"
#include "VertexArray.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Sharon
{
    VertexArray* VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::None:   SHARON_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
        case RendererAPI::OpenGL: return new OpenGLVertexArray();
        }

        SHARON_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }
} 