#include "Camera.h"

Camera::Camera()
{
    position   = glm::vec3(0.0f, 0.0f,  3.0f);
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    up    = glm::vec3(0.0f, 1.0f,  0.0f);
    view = glm::mat4(1.f);
    view = glm::lookAt(position, position + front, up);
}

void Camera::setLastX(float newX)
{
    lX = newX;
}

void Camera::setLastY(float newY)
{
    lY = newY;
}

void Camera::setMouseSensitivity(float nS)
{
    mouseSensitivity = nS;
}

float Camera::getMouseSensitivity()
{
    return mouseSensitivity;
}

float Camera::getLastX()
{
    return lX;
}

float Camera::getLastY()
{
    return lY;
}

Camera::Camera(int x, int y, int z)
{
    position   = glm::vec3(0.0f, 0.0f,  3.0f);
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    up = glm::vec3(0.0f, 1.0f,  0.0f);
    view = glm::mat4(1.f);
    view = glm::lookAt(position, position + front, up);
}

float Camera::getSpeed()
{
    return speed;
}

void Camera::move(movement m, float speed)
{
    float prevY = position.y;
    glm::vec3 F = front;
    if(F.x < 0) F.x = -1;
    else F.x = 1;

    if(F.z < 0) F.z = -1;
    else F.z = 1;


    switch (m)
    {
    case FORWARD:
        position += frontMove * speed;
        position.y = prevY;
        break;

    case BACKWARD:
        position -= frontMove * speed;
        position.y = prevY;
        break;

    case LEFT:
        position -= right * speed;
        position.y = prevY;
        break;

    case RIGHT:
        position += right * speed;
        position.y = prevY;
        break;

    case UP:
        position.y += speed;
        break;

    case BOTTOM:
        position.y -= speed;
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
            std::cout<<view[i][j];
        }
        std::cout<<std::endl;
    }
}

void Camera::update()
{
    view = glm::lookAt(position, position + front, up);
    right = glm::normalize(glm::cross(front, up));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
}



glm::mat4 Camera::getView()
{
    return view;
}

glm::mat4 & Camera::getViewRef()
{
    return view;
}
