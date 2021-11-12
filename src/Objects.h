#ifndef OBJECTS_H
#define OBJECTS_H

#include "Object.h"
#include "Shapes.h"

class Cube : public Object
{
public:
    Cube() : Object()
    {
        setFaceCulling(true);
        setTextureTypeTo2D();
        setMesh(&Shapes::cube);
    }
    ~Cube() {}
};

class CloudContainer : public Object
{
public:
    float m_anvilAmount;
    float m_lightMultiplicator;
    float m_timeFactor;
    float m_globalCoverage;
    float m_globalDensity;
    float m_lightPower;


    glm::vec3 m_boxVmin;
    glm::vec3 m_boxVmax;
    glm::vec3 m_lightPos;

    
    CloudContainer() : Object()
    {
        setFaceCulling(false);
        setTextureTypeTo2D();
        setMesh(&Shapes::cube);
        m_anvilAmount = 0;
        m_lightMultiplicator = 10;
        m_timeFactor = 0;
        m_globalCoverage = 1.0;
        m_globalDensity = 5;
        m_lightPower = 100;

        m_boxVmin = glm::vec3(0, 0, 0);
        m_boxVmax = glm::vec3(100, 50, 100);
        m_lightPos = glm::vec3(50, 100, 50);
    }

    void setUniform(Shader & Shader, const glm::mat4 & view, const glm::mat4 & projection) override
    {
        glm::mat4 m = glm::mat4(1.f);
        glm::mat4 v = view;
        glm::mat4 p = projection;

        float m_time = 0;

        glm::mat4 mvp = p * v * m;
        glm::mat4 mvpInv = glm::inverse(mvp);

        Shader.setVec3("nuage", "vmin", m_boxVmin);
        Shader.setVec3("nuage","vmax", m_boxVmax);
        Shader.setVec3("nuage","lightpos", m_lightPos);
        Shader.setFloat("nuage","lightpower", m_lightPower);
        Shader.setFloat("nuage","lightMultiplicator", m_lightMultiplicator);

        Shader.setMat4("nuage","view", view);
        Shader.setMat4("nuage","projection", projection);
        Shader.setMat4("nuage","mvpMatrix", mvp);
        Shader.setMat4("nuage","mvpInvMatrix", mvpInv);

        Shader.setFloat("nuage","time", m_timeFactor);

        Shader.setFloat("nuage","globalCoverage", m_globalCoverage);
        Shader.setFloat("nuage","globalDensity", m_globalDensity);
        Shader.setFloat("nuage","anvilAmount", m_anvilAmount);
    }
    ~CloudContainer() {}
};



#endif //OBJECTS_H