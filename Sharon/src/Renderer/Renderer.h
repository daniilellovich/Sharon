#pragma once
#include "RenderCommand.h"

namespace Sharon
{
    class Renderer
    {
    public:
        static void BeginScene();
        static void EndScene();

        static void Sumbit(const std::shared_ptr<VertexArray>& vertexArray);

        static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
    };
}