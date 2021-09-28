#include "Camera.h"

Camera::Camera()
{
    m_position   = glm::vec3(0.0f, 0.0f,  3.0f);
    m_front = glm::vec3(0.0f, 0.0f, -1.0f);
    m_up    = glm::vec3(0.0f, 1.0f,  0.0f);
    m_view = glm::mat4(1.f);
    m_view = glm::lookAt(m_position, m_position + m_front, m_up);
}

void Camera::setLastX(float newX)
{
    m_lastX = newX;
}

void Camera::setLastY(float newY)
{
    m_lastY = newY;
}

void Camera::setMouseSensitivity(float nS)
{
    m_mouseSensitivity = nS;
}

float Camera::getMouseSensitivity()
{
    return m_mouseSensitivity;
}

float Camera::getLastX()
{
    return m_lastX;
}

float Camera::getLastY()
{
    return m_lastY;
}

Camera::Camera(int x, int y, int z)
{
    m_position = glm::vec3(0.0f, 0.0f,  0.0f);
    m_front = glm::vec3(0.0f, 0.0f, 0.0f);
    m_up = glm::vec3(0.0f, 1.0f,  0.0f);
    m_view = glm::mat4(1.f);
    m_view = glm::lookAt(m_position, m_position + m_front, m_up);
}

float Camera::getSpeed()
{
    return m_speed;
}

void Camera::move(Movement m, float speed)
{
    float prevY = m_position.y;
    glm::vec3 F = m_front;
    if(F.x < 0) F.x = -1;
    else F.x = 1;

    if(F.z < 0) F.z = -1;
    else F.z = 1;


    switch (m)
    {
    case FORWARD:
        m_position += m_frontMove * speed;
        m_position.y = prevY;
        break;

    case BACKWARD:
        m_position -= m_frontMove * speed;
        m_position.y = prevY;
        break;

    case LEFT:
        m_position -= m_right * speed;
        m_position.y = prevY;
        break;

    case RIGHT:
        m_position += m_right * speed;
        m_position.y = prevY;
        break;

    case UP:
        m_position.y += speed;
        break;

    case BOTTOM:
        m_position.y -= speed;
        break;

    default:
        break;
    }

}

void Camera::printView()
{
    std::cout<<"matriceView ::"<<std::endl;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            std::cout<<m_view[i][j];
        }
        std::cout<<std::endl;
    }
}

void Camera::update()
{
    m_view = glm::lookAt(m_position, m_position + m_front, m_up);
    m_right = glm::normalize(glm::cross(m_front, m_up));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
}



glm::mat4 Camera::getView()
{
    return m_view;
}

glm::mat4 & Camera::getViewRef()
{
    return m_view;
}
