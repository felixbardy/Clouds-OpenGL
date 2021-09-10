#ifndef DEF_MESH
#define DEF_MESH

#include "glad.h"
#include <iostream>
#include <vector>
#include "shader.h"
#include "textures.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class mesh
{
    public:
    std::vector<uint> indices;

    mesh();
    ~mesh();

    
    glm::mat4 model;

    std::vector<glm::vec3> position;

    void rotate(float angle, glm::vec3 vAxis);
    void scale(glm::vec3 vScale);
    void translate(glm::vec3 vTranslate);
    void draw(shader * shaderToUse, glm::mat4& projection, glm::mat4& view);
    
    
    void render(float angle, shader & Shader, glm::mat4 & projection, glm::mat4 & view);
    void setPosition(std::vector<glm::vec3> positions);
    void setPolygon(const textures& texture, std::vector<float> vertexArray, std::vector<float> u, std::vector<uint> uvIndex, std::vector<float> c, std::vector<uint> indicesArray);
    void setTriangle(std::vector<float> u = {}, std::vector<uint> uI = {}, std::vector<float> c = {});
    void setSquare(std::vector<float> u = {}, std::vector<uint> uI = {}, std::vector<float> c = {});
    void setCube(const textures & texture, std::vector<float> u = {},  std::vector<uint> uI = {}, std::vector<float> c = {});
    void resetModel();
    uint & getVAO();

    unsigned int VAO, VBO, EBO;

    void init();

    private:

    std::vector<float> vertex;

    void initVBO();
    void initVAO();
    void initEBO();

};

#endif