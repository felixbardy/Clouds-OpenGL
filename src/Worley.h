#ifndef DEF_UTILITY
#define DEF_UTILITY

#include <string>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
/** @class Worley
 * @brief Module générateur de bruit de worley
*/
class Worley
{
    public:

    Worley(float s, int w, int h, int d);

    float get3d(float x, float y, float z);
    float get3d(glm::vec3 position);

    void setScale(float scale);
    float getScale();

    void setWidth(int w);
    void setHeight(int h);
    void setDepth(int d);

    int getWidth();
    int getHeight();
    int getDepth();
    
    void enableGrid();
    void enablePoint();
    void enablePropagation();

    void disableGrid();
    void disablePoint();
    void disablePropagation();

    private:

    float scale;
    bool drawPropagation, drawGrid, drawPoint;

    int width, height, depth;

    glm::vec3 random3(glm::vec3 p);
};

#endif