#include "sharon_pch.h"
#include "OrthographicCamera.h"

#include "glm/gtc/matrix_transform.hpp"

namespace Sharon 
{
    Sharon::OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
        : m_ProjMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f)
    {
        m_ViewProjMatrix = m_ProjMatrix * m_ViewMatrix;
    }

    void Sharon::OrthographicCamera::RecaluclateViewMatrix()
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
            glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));
        
        m_ViewMatrix = glm::inverse(transform);
        m_ViewProjMatrix = m_ProjMatrix * m_ViewMatrix; // for OpenGL
    }
}