#include "Mesh.h"
#include <iostream>


Mesh::Mesh()
{
    m_model = glm::mat4(1.f);
    m_position = {
        glm::vec3(0.f, 0.f, 0.f)
    };
}

/*void Mesh::setPolygon(const Textures& texture, std::vector<float> vertexArray, std::vector<float> u, std::vector<uint> uI, std::vector<float> c, std::vector<uint> indicesArray, uint id)
{
    m_indices = indicesArray;

    for(int i = 0; i < indicesArray.size(); i++)
    {
        for(int j = 0; j < 3; j++)
        {
            m_vertex.push_back(vertexArray[indicesArray[i] * 3 + j]);
        }
        for(int j = 0; j < 3; j++)
        {
            if(!c.empty())
            {
                m_vertex.push_back(c[uI[i] * 3 + j]);
            }
            else
            {
                m_vertex.push_back(1.f);
            }
        }
        for(int j = 0; j < 3; j++)
        {
            m_vertex.push_back(vertexArray[indicesArray[i] * 3 + j]);
        }
    }
    init();
}*/

void Mesh::setPolygon(const Textures& texture, std::vector<float> vertexArray, std::vector<float> u, std::vector<uint> uI, std::vector<float> c, std::vector<uint> indicesArray, uint id)
{
    m_indices = indicesArray;


    for(int i = 0; i < indicesArray.size(); i++)
    {
        for(int j = 0; j < 3; j++)
        {
            m_vertex.push_back(vertexArray[indicesArray[i] * 3 + j]);
        }
        for(int j = 0; j < 3; j++)
        {
            if(!c.empty())
            {
                m_vertex.push_back(c[uI[i] * 3 + j]);
            }
            else
            {
                m_vertex.push_back(1.f);
            }
        }
        for(int j = 0; j < 2; j++)
        {
            if(!u.empty())
            {
                m_vertex.push_back(u[uI[i] * 2 + j]);
            }
            else
            {
                m_vertex.push_back(1.f);
            }
        }
    }
    init();
}



void Mesh::setCube(const Textures & texture, uint id, std::vector<float> u, std::vector<uint> uI, std::vector<float> c)
{
    std::vector<float> v =
    {
        0.f, 1.f, 0.f,   // Top Left front 0
        1.f, 1.f, 0.f,   // Top Right front 1
        0.f, 0.f, 0.f,   // Bottom Left front 2
        1.f, 0.f, 0.f,   // Bottom Right front 3

        0.f, 1.f, 1.f,   // Top Left back 4
        1.f, 1.f, 1.f,   // Top Right back 5
        0.f, 0.f, 1.f,   // Bottom Left back 6
        1.f, 0.f, 1.f    // Bottom Right back 7
       /**
        *   4 - 5
        *  /   /|
        * 0 - 1 7
        * |   |/
        * 2 - 3
        * 
        * 
       */
    };

    std::vector<uint> s =
    {
        // AVANT ARRIERE
        0, 1, 2,
        2, 1, 3,

        5, 4, 7,
        7, 4, 6,

        // DROITE GAUCHE
        1, 5, 3,
        3, 5, 7,

        4, 6, 0,
        0, 6, 2,

        // HAUT BAS
        4, 5, 0,
        0, 5, 1,

        6, 2, 7,
        7, 2, 3


    };
    setPolygon(texture, v, u, uI, c, s, 0);
}

void Mesh::init()
{
    initVBO();
    initVAO();
    initEBO();
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glEnable(GL_DEPTH_TEST);
}

void Mesh::initVAO()
{
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);// Bind l'objet a la CG
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO); // Lie le buffer de data aux attribues du m_VAO
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_vertex.size(), &m_vertex[0], GL_STATIC_DRAW); // Lie les VAOdata auVAO m_VAO

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, /*9*/ 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, /*9*/ 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2/*3*/, GL_FLOAT, GL_FALSE, /*9*/ 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

void Mesh::rotate(float angle, glm::vec3 vAxis)
{
    m_model = glm::rotate(m_model, angle, vAxis);
}
void Mesh::scale(glm::vec3 vScale)
{
    m_model =  glm::scale(m_model, vScale);
}
void Mesh::translate(glm::vec3 vTranslate)
{
    m_model = glm::translate(m_model, vTranslate);
}
void Mesh::resetModel()
{
    m_model = glm::mat4(1.f);
}

void Mesh::draw(Shader * shaderToUse, glm::mat4& projection, glm::mat4& view)
{
    shaderToUse->setMat4("model", m_model);
    glBindVertexArray(m_VAO);
    //std::cout<<m_vertex.size()/8<<std::endl;
    //glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, m_vertex.size()/8/*9*/);
    m_model = glm::mat4(1.f);
}

void Mesh::initVBO()
{
    // Permet de créer une zone mémoire dans la CG pour stocker le vertice;
    glGenBuffers(1, &m_VBO); // Genere l'ID du buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO); // Attribution de son type
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_vertex.size(), &m_vertex[0], GL_STATIC_DRAW); // Lie les VAOdata auVAO m_VAO
}

void Mesh::initEBO()
{
    glGenBuffers(1, &m_EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * m_indices.size(), &m_indices[0], GL_STATIC_DRAW);
}

uint& Mesh::getVAO()
{
    return m_VAO;
}

void Mesh::render(float angle, Shader & Shader, glm::mat4& projection, glm::mat4& view)
{
    for(int i = 0; i < m_position.size(); i++)
    {
        resetModel();
        //rotate(angle/10.f, glm::vec3(glm::cos(m_position[i].x), log2(m_position[i].y), sin(m_position[i].z)));
        translate(m_position[i] + glm::vec3(-8, -8, -8));
        scale(glm::vec3(16, 16, 16));
        //rotate(m_position[i].length, glm::vec3(1.f));
        draw(&Shader, projection, view);
    }
}

void Mesh::setPosition(std::vector<glm::vec3> positions)
{
    m_position = positions;
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
}
