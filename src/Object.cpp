#include "Object.h"
#include <iostream>


Object::Object() :
is2D(false), has_face_culling(true), m_model(glm::mat4(1.f)),
m_position({glm::vec3(0.f)}), m_shaderKey("basic2D")
{

}

Object::~Object()
{
    
}


Object& Object::rotate(float angle, glm::vec3 vAxis)
{
    m_model = glm::rotate(m_model, angle, vAxis);
    return *this;
}
Object& Object::scale(glm::vec3 vScale)
{
    m_model =  glm::scale(m_model, vScale);
    return *this;
}
Object& Object::translate(glm::vec3 vTranslate)
{
    m_model = glm::translate(m_model, vTranslate);
    return *this;
}

Object& Object::setFaceCulling(bool face_culling) {
    this->has_face_culling = face_culling;
    return *this;
}

bool Object::getFaceCulling() const { return has_face_culling; }

Object& Object::setShaderKey(const std::string & shaderKey)
{
    m_shaderKey = shaderKey;
    return *this;
}

std::string Object::getShaderKey() const
{
    return m_shaderKey;
}



Object& Object::resetModel()
{
    m_model = glm::mat4(1.f);
    return *this;
}

void Object::draw()
{
    glBindVertexArray(m_mesh->getVAO());
    glDrawArrays(GL_TRIANGLES, 0, m_mesh->getVertexCount());
}


Object& Object::setTextureKeys(std::vector<std::string> keys)
{
    m_texturesKeys.insert(m_texturesKeys.end(), keys.begin(), keys.end());
    return *this;
}

Object& Object::setTextureTypeTo3D()
{
    is2D = false;
    return *this;
}
Object& Object::setTextureTypeTo2D()
{
    is2D = true;
    return *this;
}

void Object::setUniform(Shader & Shader, const glm::mat4 & view, const glm::mat4 & projection)
{
    Shader.use(m_shaderKey);
    Shader.setMat4(m_shaderKey, "view", view);
    Shader.setMat4(m_shaderKey, "projection", projection);
}

void Object::render(Shader & Shader, Textures & textureManager, const glm::mat4 & view, const glm::mat4 & projection)
{
    setUniform(Shader, view, projection);
    // Si l'objet ne doit pas masquer l'environnement
    // activer puis désactiver le face culling
    if (!has_face_culling) glDisable(GL_CULL_FACE);

    for(int i = 0; i < m_texturesKeys.size(); i++)
    {
        if(is2D)
        {
            textureManager.use2D(m_texturesKeys[i], i);
            //std::cout<<"2D = "<<m_texturesKeys[i]<<std::endl;
        }
        else
        {
            textureManager.use3D(m_texturesKeys[i], i);
            //std::cout<<"3D = "<<m_texturesKeys[i]<<std::endl;
        }
    }

    resetModel();
    translate(m_position);
    Shader.setMat4(m_shaderKey, "model", m_model);
    draw();
    m_model = glm::mat4(1.f);

    if (!has_face_culling) glEnable(GL_CULL_FACE);
}

void Object::setMesh(Mesh * newMesh)
{
    m_mesh = newMesh;
}


Object& Object::setPosition(glm::vec3 position)
{
    m_position = position;
    return *this;
}

