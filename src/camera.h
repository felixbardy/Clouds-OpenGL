#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
enum movement{FORWARD, BACKWARD, LEFT, RIGHT, UP, BOTTOM};
class camera
{
    public: 
    
    glm::mat4 & getViewRef();
    glm::mat4 getView();

    
    
    camera(int x, int y, int z);
    camera();

    void update();

    float getSpeed();
    void move(movement m, float speed);
    glm::vec3 position, up, right;

    void printView();

    float lX = 0;
    float lY = 0;
    bool initMouse = true;
    float mouseSensitivity = 0.1f;
    float yawD = -90.f;
    float pitchD = 0.f;
    glm::vec3 front = glm::vec3(0.f, 0.f, -1.f);

    private:

    glm::mat4 view;
    float speed = 3.f;
    
};