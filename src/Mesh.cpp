#include "Mesh.h"
#include <iostream>


Mesh::Mesh()
{
    m_model = glm::mat4(1.f);
    m_position = {
        glm::vec3(0.f, 0.f, 0.f)
    };
    m_shaderKey = "basic2D";
}

void Mesh::setPolygon(std::vector<float> vertices, std::vector<uint> verticesOrder, std::vector<float> uvArray, std::vector<uint> uvOrder, std::vector<float> color, std::vector<uint> colorOrder)
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
}



void Mesh::setCube()
{
   /** Vertex Order Scheme
	 *		   4 - 5
	 *		  /   /|
	 *		 0 - 1 7
	 *		 |   |/
	 *		 2 - 3
	*/
    std::vector<float> vertices =
    {
        0.f, 1.f, 0.f,   // Top Left front 0
        1.f, 1.f, 0.f,   // Top Right front 1
        0.f, 0.f, 0.f,   // Bottom Left front 2
        1.f, 0.f, 0.f,   // Bottom Right front 3

        0.f, 1.f, 1.f,   // Top Left back 4
        1.f, 1.f, 1.f,   // Top Right back 5
        0.f, 0.f, 1.f,   // Bottom Left back 6
        1.f, 0.f, 1.f    // Bottom Right back 7
    };

    std::vector<uint> verticesOrder =
    {
        // AVANT ARRIERE
        0, 1, 2,
        2, 1, 3,

        5, 4, 7,
        7, 4, 6,

        // DROITE GAUCHE
        1, 5, 3,
        3, 5, 7,

        4, 0, 6,
        6, 0, 2,

        // HAUT BAS
        4, 5, 0,
        0, 5, 1,

        6, 2, 7,
        7, 2, 3
    };

    std::vector<float> uv =
    {
        0.f, 0.f,
        0.f, 1.f,
        1.f, 1.f,
        1.f, 0.f
    };

    std::vector<uint> uvIndex
    {
        1, 2, 0,
        0, 2, 3,

        1, 2, 0,
        0, 2, 3,

        1, 2, 0,
        0, 2, 3,

        1, 2, 0,
        0, 2, 3,

        3, 0, 2,
        2, 0, 1,

        0, 1, 3,
        3, 1, 2
    };

    /*std::vector<float> color
    {
        1, 0, 0,
        0, 1, 0,
        0, 0, 1,
        1, 1, 0,
        0, 1, 1,
        1, 0, 1
    };

    std::vector<uint> colorId =
    {
        // AVANT ARRIERE
        0, 1, 2,
        2, 1, 3,

        5, 4, 7,
        7, 4, 6,

        // DROITE GAUCHE
        1, 5, 3,
        3, 5, 7,

        4, 0, 6,
        6, 0, 2,

        // HAUT BAS
        4, 5, 0,
        0, 5, 1,

        6, 2, 7,
        7, 2, 3
    };*/
    setPolygon(vertices, verticesOrder, uv, uvIndex/*, color, colorId*/);
}

void Mesh::setShaderKey(const std::string & shaderKey)
{
    m_shaderKey = shaderKey;
}

std::string Mesh::getShaderKey()
{
    return m_shaderKey;
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

void Mesh::draw()
{
    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, m_vertex.size()/8/*9*/);
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

void Mesh::setTextureKeys(std::vector<std::string> keys)
{
    m_texturesKeys.insert(m_texturesKeys.end(), keys.begin(), keys.end());
}

void Mesh::setTextureTypeTo3D()
{
    is2D = false;
}
void Mesh::setTextureTypeTo2D()
{
    is2D = true;
}

void Mesh::render(Shader & Shader, Textures & textureManager, const glm::mat4 & view, const glm::mat4 & projection, float angle)
{
    Shader.use(m_shaderKey);
    Shader.setMat4(m_shaderKey, "view", view);
    Shader.setMat4(m_shaderKey, "projection", projection);
    Shader.setFloat(m_shaderKey, "time", angle);

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
    for(int i = 0; i < m_position.size(); i++)
    {
        resetModel();
        translate(m_position[i]);
        Shader.setMat4(m_shaderKey, "model", m_model);
        draw();
        m_model = glm::mat4(1.f);
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
