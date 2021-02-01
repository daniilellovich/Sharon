#include "sharon_pch.h"
#include "Buffer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

#include "Renderer.h"

namespace Sharon
{
    VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::None:   SHARON_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
        case RendererAPI::OpenGL: return new OpenGLVertexBuffer(vertices, size);
        }

        SHARON_CORE_ASSERT(false, "Unknown RendererAPI"); 
        return nullptr;
    }

    IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::None:   SHARON_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
        case RendererAPI::OpenGL: return new OpenGLIndexBuffer(indices, size);
        }

        SHARON_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }
}