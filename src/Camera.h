#ifndef DEF_CAMERA
#define DEF_CAMERA

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
enum movement{FORWARD, BACKWARD, LEFT, RIGHT, UP, BOTTOM};
class Camera
{
    public:

    glm::mat4 & getViewRef();
    glm::mat4 getView();

    Camera(int x, int y, int z);
    Camera();

    void update();

    float getSpeed();
    void move(movement m, float speed);
    glm::vec3 position, up, right;

    float getLastX();
    float getLastY();

    void setLastX(float newX);
    void setLastY(float newY);

    void printView();

    float getMouseSensitivity();
    void setMouseSensitivity(float newSensitivity);

    bool initMouse = true;
    float yawD = -90.f;
    float pitchD = 0.f;
    glm::vec3 front = glm::vec3(0.f, 0.f, -1.f);
    glm::vec3 frontMove = front;

    private:

    float lX = 0;
    float lY = 0;
    float mouseSensitivity = 0.1f;
    glm::mat4 view;
    float speed = 3.f;

};

#endif
