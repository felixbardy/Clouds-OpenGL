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
    m_width = w;
}

int Worley::getWidth()
{
    return m_width;
}

void Worley::setHeight(int h)
{
    m_height = h;
}

int Worley::getHeight()
{
    return m_height;
}

void Worley::setDepth(int d)
{
    m_depth = d;
}

int Worley::getDepth()
{
    return m_depth;
}

void Worley::setScale(float s)
{
    m_scale = s;
}

float Worley::getScale()
{
    return m_scale;
}

void Worley::enableGrid()
{
    m_drawGrid = true;
}
void Worley::disableGrid()
{
    m_drawGrid = false;
}
void Worley::enablePoint()
{
    m_drawPoint = true;
}
void Worley::disablePoint()
{
    m_drawPoint = false;
}
void Worley::enablePropagation()
{
    m_drawPropagation = true;
}
void Worley::disablePropagation()
{
    m_drawPropagation = false;
}

float Worley::get3d(glm::vec3 position)
{
    position.x /= (float)getWidth();
    position.y /= (float)getHeight();
    position.z /= (float)getDepth();
    //std::cout<<position.x<<" "<<position.y<<" "<<position.z<<std::endl;
    glm::vec3 st = position;
    st *= getScale();
    glm::vec3 intPos = glm::vec3(glm::floor(st.x), glm::floor(st.y), glm::floor(st.z));
    glm::vec3 decimPos = glm::vec3(st.x - intPos.x, st.y - intPos.y, st.z  - intPos.z);
    //std::cout<<" I : x = "<<intPos.x<<" y = "<<intPos.y<<" z = "<<intPos.z<<std::endl;
    //std::cout<<" F : x = "<<decimPos.x<<" y = "<<decimPos.y<<" z = "<<decimPos.z<<std::endl;
    float color = 0;

    float minimalDistance = 1;
    

    for(int x = -1; x <= 1; x++)
    {
        for(int y = -1; y <= 1; y++)
        {
            for(int z = -1; z <= 1; z++)
            {
                glm::vec3 voisin = glm::vec3(float(x), float(y), float(z));
                glm::vec3 point = random3(intPos + voisin);
                glm::vec3 diff = (voisin + point) - decimPos;
                float dist = glm::length(diff);
                minimalDistance = glm::min(minimalDistance, dist);
            }
        }
    }

    color += minimalDistance;

    if(m_drawPropagation)
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
    
    if(m_drawPoint)
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

    if(m_drawGrid)
    {
        // Draw grid
        if(decimPos.x < 0.98)
        {
            color += 0;
        }
        else
        {
            color += 1;
        }
        
        if(decimPos.y < 0.98)
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