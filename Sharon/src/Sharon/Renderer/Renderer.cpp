#include "sharon_pch.h"
#include "Renderer.h"

namespace Sharon
{
    Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

    void Renderer::BeginScene(OrthographicCamera& camera)
    {
        m_SceneData->ViewProjMatrix = camera.GetViewProjMatrix();
    }

    //void Renderer::BeginScene(ProjectionCamera& camera)
    //{
    //    m_SceneData->ViewProjMatrix = camera.GetViewProjMatrix();
    //}

    void Renderer::EndScene()
    {

    }

    void Renderer::Sumbit(const std::shared_ptr<VertexArray>& vertexArray, 
        glm::mat4& model,
        const std::shared_ptr<Shader>& shader)
    {
        vertexArray->Bind();
        
        shader->Bind();
        shader->UploadUniformMat4("u_ViewProj", m_SceneData->ViewProjMatrix);
        shader->UploadUniformMat4("u_Model", model);

        RenderCommand::DrawIndexed(vertexArray);
    }
}