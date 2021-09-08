#include "mesh.h"
#include <iostream>


mesh::mesh()
{
    model = glm::mat4(1.f);
}

void mesh::setPolygon(std::vector<float> vertexArray, std::vector<float> u, std::vector<uint> uI, std::vector<float> c, std::vector<uint> indicesArray)
{
    indices = indicesArray;
    //std::cout<<indicesArray.size()<<std::endl;
    for(int i = 0; i < indicesArray.size(); i++)
    {
        for(int j = 0; j < 3; j++)
        {
            vertex.push_back(vertexArray[indicesArray[i] * 3 + j]);
        }
        for(int j = 0; j < 3; j++)
        {
            if(!c.empty())
            {
                vertex.push_back(c[uI[i] * 3 + j]);
            }
            else
            {
                vertex.push_back(1.f);
            }
        }
        for(int j = 0; j < 2; j++)
        {
            if(!u.empty())
            {
                vertex.push_back(u[uI[i] * 2 + j]);
            }
            else
            {
                vertex.push_back(1.f);
            }
        }
        //std::cout<<"size = "<<vertex.size()<<std::endl;
        
    }
    init();
}

void mesh::setSquare(std::vector<float> u, std::vector<uint> uI,  std::vector<float> c)
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

    setPolygon(v, u, uI, c, s);
}

void mesh::setCube(std::vector<float> u, std::vector<uint> uI, std::vector<float> c)
{
    std::vector<float> v = 
    {
        0.5f,  0.5f, 0.5f,  // top right        3--0
        0.5f, -0.5f, 0.5f,  // bottom right     |  |
        -0.5f, -0.5f, 0.5f,  // bottom left     2--1
        -0.5f,  0.5f, 0.5f,   // top left
        
        0.5f,  0.5f, -0.5f,  // top right        7--4
        0.5f, -0.5f, -0.5f,  // bottom right     |  |
        -0.5f, -0.5f, -0.5f,  // bottom left     6--5
        -0.5f,  0.5f, -0.5f   // top left
    };

    /*
      7--4  
     /  /|
    3--0 5
    |  |/
    2--1
    */

    std::vector<uint> s = 
    {
        // AVANT ARRIERE
        3, 0, 2, 
        2, 0, 1,

        7, 6, 4,
        4, 6, 5,

        // GAUCHE DROITE
        7, 6, 3,
        3, 6, 2,

        0, 4, 1,
        1, 4, 5,

        // HAUT BAS
        7, 4, 3,
        3, 4, 0,

        2, 6, 1,
        1, 6, 5

    };

    setPolygon(v, u, uI, c, s);
}

void mesh::setTriangle(std::vector<float> u, std::vector<uint> uI, std::vector<float> c)
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

    setPolygon(v, u, uI, c, s);
} 

void mesh::init()
{
    initVBO();
    initVAO();
    initEBO();
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glEnable(GL_DEPTH_TEST);  
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
    model = glm::rotate(model, angle, vAxis);
}
void mesh::scale(glm::vec3 vScale)
{
    model =  glm::scale(model, vScale);
}
void mesh::translate(glm::vec3 vTranslate)
{
    model = glm::translate(model, vTranslate);
}
void mesh::resetModel()
{
    model = glm::mat4(1.f);
}

void mesh::draw(shader * shaderToUse, glm::mat4 projection, glm::mat4 view)
{
    shaderToUse->transform(model);
    glBindVertexArray(VAO);
    //std::cout<<vertex.size()/8<<std::endl;
    //glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, vertex.size()/8);
    model = glm::mat4(1.f);
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
