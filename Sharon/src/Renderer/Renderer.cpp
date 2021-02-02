#include "sharon_pch.h"
#include "Renderer.h"

namespace Sharon
{
    void Renderer::BeginScene()
    {

    }

    void Renderer::EndScene()
    {

    }

    void Renderer::Sumbit(const std::shared_ptr<VertexArray>& vertexArray)
    {
        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }
}