#include "Worley.h"

Worley::Worley(float s, int w, int h, int d)
{
    setScale(s);
    disablePropagation();
    disableGrid();
    disablePoint();
    setWidth(w);
    setHeight(h);
    setDepth(d);
}

void Worley::setWidth(int w)
{
    width = w;
}

int Worley::getWidth()
{
    return width;
}

void Worley::setHeight(int h)
{
    height = h;
}

int Worley::getHeight()
{
    return height;
}

void Worley::setDepth(int d)
{
    depth = d;
}

int Worley::getDepth()
{
    return depth;
}

void Worley::setScale(float s)
{
    scale = s;
}

float Worley::getScale()
{
    return scale;
}

void Worley::enableGrid()
{
    drawGrid = true;
}
void Worley::disableGrid()
{
    drawGrid = false;
}
void Worley::enablePoint()
{
    drawPoint = true;
}
void Worley::disablePoint()
{
    drawPoint = false;
}
void Worley::enablePropagation()
{
    drawPropagation = true;
}
void Worley::disablePropagation()
{
    drawPropagation = false;
}

float Worley::get3d(glm::vec3 position)
{
    position.x /= (float)getWidth();
    position.y /= (float)getHeight();
    position.z /= (float)getDepth();
    //std::cout<<position.x<<" "<<position.y<<" "<<position.z<<std::endl;
    glm::vec3 st = position;
    st *= getScale();
    glm::vec3 i_st = glm::vec3(glm::floor(st.x), glm::floor(st.y), glm::floor(st.z));
    glm::vec3 f_st = glm::vec3(st.x - i_st.x, st.y - i_st.y, st.z  - i_st.z);
    //std::cout<<" I : x = "<<i_st.x<<" y = "<<i_st.y<<" z = "<<i_st.z<<std::endl;
    //std::cout<<" F : x = "<<f_st.x<<" y = "<<f_st.y<<" z = "<<f_st.z<<std::endl;
    float color = 0;

    float minimalDistance = 1;
    

    for(int x = -1; x <= 1; x++)
    {
        for(int y = -1; y <= 1; y++)
        {
            for(int z = -1; z <= 1; z++)
            {
                glm::vec3 voisin = glm::vec3(float(x), float(y), float(z));
                glm::vec3 point = random3(i_st + voisin);
                glm::vec3 diff = (voisin + point) - f_st;
                float dist = glm::length(diff);
                minimalDistance = glm::min(minimalDistance, dist);
            }
        }
    }

    color += minimalDistance;

    if(drawPropagation)
    {
        // Draw Propagation
        if(abs(sin(50.0*minimalDistance)) < 0.7)
        {
            color = 0;
        }
        else
        {
            color = 0.3;
        }
    }
    
    if(drawPoint)
    {
        // Draw Points
        if(minimalDistance < 0.02)
        {
            color += 0;
        }
        else
        {
            color += 1;
        }
    }

    if(drawGrid)
    {
        // Draw grid
        if(f_st.x < 0.98)
        {
            color += 0;
        }
        else
        {
            color += 1;
        }
        
        if(f_st.y < 0.98)
        {
            color += 0;
        }
        else
        {
            color += 1;
        }
    }
    return 1 - color;
}

float Worley::get3d(float x, float y, float z)
{
    return get3d(glm::vec3(x, y, z));
}

glm::vec3 Worley::random3(glm::vec3 p) 
{
    glm::vec3 toMult = sin(glm::vec3(
        dot(p,glm::vec3(127.1,311.7, 214.4)),
        dot(p,glm::vec3(269.5,183.3, 107.5)),
        dot(p,glm::vec3(114.5,413.3, 49.5))
        ));

    glm::vec3 toFrac = glm::vec3(toMult.x * 43758.5453, toMult.y * 43758.5453, toMult.z * 43758.5453);

    return glm::vec3(toFrac.x - floor(toFrac.x), toFrac.y - floor(toFrac.y), toFrac.z - floor(toFrac.z));
}