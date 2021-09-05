#include "mesh.h"
#include <iostream>


mesh::mesh()
{
    transform = glm::mat4(1.f);
}

void mesh::setPolygon(std::vector<float> vertexArray, std::vector<float> u, std::vector<float> c, std::vector<uint> indicesArray)
{
    
    indices = indicesArray;
    for(int j = 0; j < vertexArray.size()/3; j++)
    {
        for(int i = 0; i < 3; i++)
        {
            vertex.push_back(vertexArray[j*3+i]);
        }
        for(int i = 0; i < 3; i++)
        {
            if(!c.empty())
            {
                vertex.push_back(c[j*3+i]);
            }
            else
            {
                vertex.push_back(1.0f);
            }
        }
        for(int i = 0; i < 2; i++)
        {
            if(!u.empty())
            {
                vertex.push_back(u[j*2+i]);
            }
            else
            {
                vertex.push_back(1.0f);
            }
        }
    }
    init();
}

void mesh::setSquare(std::vector<float> u, std::vector<float> c)
{
    std::vector<float> v = 
    {
        0.5f,  0.5f, 0.0f,  // top right        3--0
        0.5f, -0.5f, 0.0f,  // bottom right     |  |
        -0.5f, -0.5f, 0.0f,  // bottom left     2--1
        -0.5f,  0.5f, 0.0f   // top left 
    };

    std::vector<uint> s = 
    {
        3, 0, 2,
        2, 0, 1
    };

    setPolygon(v, u, c, s);
}

void mesh::setTriangle(std::vector<float> u, std::vector<float> c)
{
    std::vector<float> v = 
   {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    std::vector<uint> s =
    {
        0, 1, 2    
    };

    setPolygon(v, u, c, s);
}

void mesh::init()
{
    initVBO();
    initVAO();
    initEBO();
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void mesh::initVAO()
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);// Bind l'objet a la CG
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // Lie le buffer de data aux attribues du VAO
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex.size(), &vertex[0], GL_STATIC_DRAW); // Lie les VAOdata auVAO VAO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);  
}

void mesh::rotate(float angle, glm::vec3 vAxis)
{
    transform = glm::rotate(transform, angle, vAxis);
}
void mesh::scale(glm::vec3 vScale)
{
    transform =  glm::scale(transform, vScale);
}
void mesh::translate(glm::vec3 vTranslate)
{
    transform = glm::translate(transform, vTranslate);
}
void mesh::draw(shader * shaderToUse)
{
    shaderToUse->transform(transform);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    transform = glm::mat4(1.f);
}

void mesh::initVBO()
{
    // Permet de créer une zone mémoire dans la CG pour stocker le vertice;
    glGenBuffers(1, &VBO); // Genere l'ID du buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // Attribution de son type
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex.size(), &vertex[0], GL_STATIC_DRAW); // Lie les VAOdata auVAO VAO
}

void mesh::initEBO()
{
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * indices.size(), &indices[0], GL_STATIC_DRAW);
}

uint& mesh::getVAO()
{
    return VAO;
}

mesh::~mesh()
{
    std::cout<<"Destruction de la mesh"<<std::endl;
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    std::cout<<"Destruction termine"<<std::endl;
}
