#include "Mesh.h"


Mesh::Mesh(/* args */)
{

}


Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
}

void Mesh::initVBO()
{
    // Permet de créer une zone mémoire dans la CG pour stocker le vertice;
    glGenBuffers(1, &m_VBO); // Genere l'ID du buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO); // Attribution de son type
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_vertex.size(), &m_vertex[0], GL_STATIC_DRAW); // Lie les VAOdata auVAO m_VAO
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

void Mesh::initEBO()
{
    glGenBuffers(1, &m_EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * m_indices.size(), &m_indices[0], GL_STATIC_DRAW);
}

uint Mesh::getVAO() const
{
    return m_VAO;
}

uint Mesh::getVertexCount() const
{
    return m_vertex.size()/8;
}

Mesh& Mesh::setPolygon(std::vector<float> vertices, std::vector<uint> verticesOrder, std::vector<float> uvArray, std::vector<uint> uvOrder, std::vector<float> color, std::vector<uint> colorOrder)
{
    // On s'assure que uvOrder et verticesOrder font la même taille
    assert(!(uvOrder.empty() && uvOrder.size() == verticesOrder.size()));

    for(int i = 0; i < verticesOrder.size(); i++)
    {
        for(int j = 0; j < 3; j++)
        {
            m_vertex.push_back(vertices[verticesOrder[i] * 3 + j]);
        }
        for(int j = 0; j < 3; j++)
        {
            if(!colorOrder.empty())
            {
                m_vertex.push_back(color[colorOrder[i] * 3 + j]);
            }
            else
            {
                m_vertex.push_back(1.f);
            }
        }
        for(int j = 0; j < 2; j++)
        {
            if(!uvOrder.empty())
            {
                m_vertex.push_back( uvArray[uvOrder[i] * 2 + j]);
            }
            else
            {
                m_vertex.push_back(1.f);
            }
        }
    }
    init(); //sure?
    return *this;
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