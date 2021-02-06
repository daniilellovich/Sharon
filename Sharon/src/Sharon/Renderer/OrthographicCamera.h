#pragma once
#include "glm/glm.hpp"

namespace Sharon 
{
    class OrthographicCamera
    {
    public:
        OrthographicCamera(float left, float right, float bottom, float top);

        const glm::vec3& GetPosition() const { return m_Position; }
        void SetPosition(const glm::vec3& position) { m_Position = position; RecaluclateViewMatrix(); }

        float GetRotation() const { return m_Rotation; }
        void SetRotation(float rotation) { m_Rotation = rotation; RecaluclateViewMatrix(); }

        const glm::mat4 GetProjMatrix() const { return m_ProjMatrix; }
        const glm::mat4 GetViewMatrix() const { return m_ViewMatrix; }
        const glm::mat4 GetViewProjMatrix() const { return m_ViewProjMatrix; }

    private:
        void RecaluclateViewMatrix();

    private:
        glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
        float m_Rotation = 0.0f; // along Z-axis

        glm::mat4 m_ProjMatrix;
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ViewProjMatrix;
    };
}
