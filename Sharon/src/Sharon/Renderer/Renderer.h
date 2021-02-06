#pragma once
#include "RenderCommand.h"
#include "OrthographicCamera.h"
#include "Shader.h"

namespace Sharon
{
    class Renderer
    {
    public:
        static void BeginScene(OrthographicCamera& camera);
        static void EndScene();

        static void Sumbit(const std::shared_ptr<VertexArray>& vertexArray, 
            glm::mat4& model,
            const std::shared_ptr<Shader>& shader);

        static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

    private:
        struct SceneData 
        {
            glm::mat4 ViewProjMatrix;
        };

        static SceneData* m_SceneData;
    };
}