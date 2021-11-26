#ifndef OBJECTS_H
#define OBJECTS_H

#include "Object.h"
#include "Shapes.h"

#include <iostream>

class Cube : public Object
{
public:
    /** @brief Constructeur de Cube
     * @param position la position de l'objet
     */
    Cube(glm::vec3 position) : Object()
    {
        setPosition(position);
        setFaceCulling(true);
        setTextureTypeTo2D();
        setMesh(&Shapes::cube);
    }
    ~Cube() {}

protected:
    void setUniforms(
        Shader& shaders,
        const glm::mat4 &model,
        const glm::mat4 &view,
        const glm::mat4 &projection
    ) override {
        return;
    }

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
    float m_minHeight;
    float m_maxHeight;
    float m_minDensity;
    float m_maxDensity;
    glm::vec3 m_lightPos;

    CloudContainer(glm::vec3 position) : Object()
    {
        setPosition(position);
        setMesh(&Shapes::cube);
        setTextureTypeTo3D();
        setFaceCulling(false);
        m_anvilAmount = 0;
        m_lightMultiplicator = 10;
        m_timeFactor = 0;
        m_globalCoverage = 1.0;
        m_globalDensity = 5;
        m_lightPower = 100;
        m_minHeight = 0.f;
        m_maxHeight = 1.f;
        m_minDensity = 0.f;
        m_maxDensity = 1.f;
        m_lightPos = glm::vec3(50, 100, 50);

    }

    void setUniforms(
        Shader& shaders,
        const glm::mat4 &model,
        const glm::mat4 &view,
        const glm::mat4 &projection
    ) override
    {
        shaders.use("nuage");
        glm::mat4 pInv = glm::inverse(projection);
        glm::mat4 vInv = glm::inverse(view);
        glm::mat4 vpInv = vInv * pInv;
        glm::mat4 m = glm::mat4(1.f);
        glm::mat4 v = view;
        glm::mat4 p = projection;

        float m_time = 0;

        glm::mat4 mvp = p * v * m;
        glm::mat4 mvpInv = glm::inverse(mvp);

        shaders.setVec3("nuage","vmin", m_position);
        shaders.setVec3("nuage","vmax", m_position + glm::vec3(1));
        shaders.setVec3("nuage","lightpos", m_lightPos);
        shaders.setFloat("nuage","lightpower", m_lightPower);
        shaders.setFloat("nuage","lightMultiplicator", m_lightMultiplicator);

        shaders.setFloat("nuage","minHeight", m_minHeight);
        shaders.setFloat("nuage","maxHeight", m_maxHeight);
        shaders.setFloat("nuage","minDensity", m_minDensity);
        shaders.setFloat("nuage","maxDensity", m_maxDensity);

        shaders.setMat4("nuage","view", view);
        shaders.setMat4("nuage","projection", projection);
        shaders.setMat4("nuage","vpInvMatrix", vpInv);
        shaders.setMat4("nuage","vpMatrix", projection * view);
        shaders.setMat4("nuage","mvpMatrix", mvp);
        shaders.setMat4("nuage","mvpInvMatrix", mvpInv);

        shaders.setFloat("nuage","time", m_timeFactor);

        shaders.setFloat("nuage","globalCoverage", m_globalCoverage);
        shaders.setFloat("nuage","globalDensity", m_globalDensity);
        shaders.setFloat("nuage","anvilAmount", m_anvilAmount);
        shaders.setFloat("nuage","temperature", 10);
    }
    
    ~CloudContainer() {}
};

class Terrain : public Object
{
public:
  Terrain() : Object()
  {
      setFaceCulling(true);
      setTextureTypeTo2D();
      setMesh(&Shapes::terrain);
  }

  void setUniforms(
        Shader& shaders,
        const glm::mat4 &model,
        const glm::mat4 &view,
        const glm::mat4 &projection
    ) override {}
    
  ~Terrain() {}
};


#endif //OBJECTS_H
