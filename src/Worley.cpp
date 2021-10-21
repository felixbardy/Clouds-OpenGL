#include "Worley.h"

Worley::Worley(float s, int w, int h, int d)
{
    setScale(s);
    setWidth(w);
    setHeight(h);
    setDepth(d);
    iniPoint();
}

//generates a psuedo-random float between 0.0 and 0.999...
float randfloat()
{
    return rand()/(float(RAND_MAX)+1);
}

//generates a psuedo-random float between 0.0 and max
float randfloat(float max)
{
    return randfloat()*max;
}

//generates a psuedo-random float between min and max
float randfloat(float min, float max)
{
    if (min>max)
    {
        return randfloat()*(min-max)+max;    
    }
    else
    {
        return randfloat()*(max-min)+min;
    }    
}

void Worley::iniPoint()
{
    
    for(int i = 0; i < getScale(); i++)
    {
        std::vector<std::vector<glm::vec3>> py;
        for(int j = 0; j < getScale(); j++)
        {
            std::vector<glm::vec3> pz;
            for(int k = 0; k < getScale(); k++)
            {
                float x, y, z;
                x = randfloat();
                y = randfloat();
                z = randfloat();
                pz.push_back(glm::vec3(x, y, z));
            }
            py.push_back(pz);
        }
        m_points.push_back(py);
    }
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

float Worley::get3d(glm::vec3 position)
{
    position.x /= (float)getWidth();
    position.y /= (float)getHeight();
    position.z /= (float)getDepth();
    //std::cout<<position.x<<" "<<position.y<<" "<<position.z<<std::endl;
    glm::vec3 st = position;
    

    st *= getScale();
    st -= getScale();
    glm::vec3 intPos = glm::vec3(glm::floor(st.x), glm::floor(st.y), glm::floor(st.z));
    glm::vec3 decimPos = glm::vec3(st.x - intPos.x, st.y - intPos.y, st.z  - intPos.z);
    float color = 0;

    float minimalDistance = 1;
    for(int i = intPos.x - 1; i <= intPos.x + 1; i++)
    {
        for(int j = intPos.y - 1; j <= intPos.y + 1; j++)
        {
            for(int k = intPos.z - 1; k <= intPos.z + 1; k++)
            {
                float x, y, z;
                if(i < -getScale()) x = getScale() - 1;
                else if(i < 0) x = getScale() + i;
                else if(i == getScale()*2) x = 0;
                else if(i >= getScale()) x = i - getScale();
                else x = i;
                
                if(j < -getScale()) y = getScale() - 1;
                else if(j < 0) y = getScale() + j;
                else if(j == getScale()*2) y = 0;
                else if(j >= getScale()) y = j - getScale();
                else y = j;

                if(k < -getScale()) z = getScale() - 1;
                else if(k < 0) z = getScale() + k;
                else if(k == getScale()*2) z = 0;
                else if(k >= getScale()) z = k - getScale();
                else z = k;
                float dist = glm::distance(st, m_points[x][y][z] + glm::vec3(i, j, k));
                if(dist < minimalDistance)
                {
                    minimalDistance = dist;
                }
                
            }
        }
    }
    color += minimalDistance;
    return 1 - color;
}

float Worley::get3d(float x, float y, float z)
{
    return get3d(glm::vec3(x, y, z));
}