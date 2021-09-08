#include "camera.h"

camera::camera()
{
    position   = glm::vec3(0.0f, 0.0f,  3.0f);
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    up    = glm::vec3(0.0f, 1.0f,  0.0f);
    view = glm::mat4(1.f);
    view = glm::lookAt(position, position + front, up);
}

camera::camera(int x, int y, int z)
{
    position   = glm::vec3(0.0f, 0.0f,  3.0f);
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    up    = glm::vec3(0.0f, 1.0f,  0.0f);
    view = glm::mat4(1.f);
    view = glm::lookAt(position, position + front, up);
}

float camera::getSpeed()
{
    return speed;
}

void camera::move(movement m, float speed)
{   
    float prevY = position.y;
    switch (m)
    {
    case FORWARD:
        position += front * speed;
        position.y = prevY;
        break;
    
    case BACKWARD:
        position -= front * speed;
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

void camera::printView()
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

void camera::update()
{
    view = glm::lookAt(position, position + front, up);
    right = glm::normalize(glm::cross(front, up));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    //up    = glm::normalize(glm::cross(right, front));

}



glm::mat4 camera::getView()
{
    return view;
}

glm::mat4 & camera::getViewRef()
{
    return view;
}