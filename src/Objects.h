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
    /** @brief Constructeur de CloudContainer
     * @param position la position de l'objet
     */
    CloudContainer(glm::vec3 position) : Object()
    {
        setPosition(position);
        setFaceCulling(false);
        setTextureTypeTo3D();
        setMesh(&Shapes::cube);
    }
    ~CloudContainer() {}

protected:
    void setUniforms(
        Shader& shaders,
        const glm::mat4 &model,
        const glm::mat4 &view,
        const glm::mat4 &projection
    ) override {

        shaders.use("nuage");
        glm::mat4 pInv = glm::inverse(projection);
        glm::mat4 vInv = glm::inverse(view);

        
        glm::mat4 vpInv = vInv * pInv;

        glm::mat4 mvp = projection * view * model;
        glm::mat4 mvpInv = glm::inverse(mvp);
        
        shaders.setVec3("nuage","vmin", m_position);
        shaders.setVec3("nuage","vmax", m_position + glm::vec3(1));
        shaders.setVec3("nuage","lightpos", glm::vec3(0,70, 0));
        shaders.setFloat("nuage","lightpower", 100);
        shaders.setFloat("nuage","lightMultiplicator", 2.5);

        shaders.setMat4("nuage","vpInvMatrix", vpInv);
        shaders.setMat4("nuage","vpMatrix", projection * view);
        shaders.setMat4("nuage","mvpMatrix", mvp);
        shaders.setMat4("nuage","mvpInvMatrix", mvpInv);

        shaders.setFloat("nuage","temperature", 10);
    }
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
