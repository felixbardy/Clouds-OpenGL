#include "Mesh.h"
#include <iostream>
#include <cassert>

Mesh::Mesh()
{
    model = glm::mat4(1.f);
    position = {
        glm::vec3(0.f, 0.f, 0.f)
    };
}


void Mesh::setPolygon(std::vector<float> vertices, std::vector<uint> verticesOrder, std::vector<float> uvArray, std::vector<uint> uvOrder)
{
		// On s'assure que uvOrder et verticesOrder font la même taille
		assert(!(uvOrder.empty() && uvOrder.size() == verticesOrder.size()));

    for(int i = 0; i < verticesOrder.size(); i++)
    {
        for(int j = 0; j < 3; j++)
        {
            vertex.push_back(vertices[verticesOrder[i] * 3 + j]);
        }
        for(int j = 0; j < 3; j++)
        {
            if(!uvOrder.empty())
            {
                vertex.push_back(uvOrder[i] * 3 + j);
            }
            else
            {
                vertex.push_back(1.f);
            }
        }
        for(int j = 0; j < 2; j++)
        {
            if(!uvOrder.empty())
            {
                vertex.push_back( uvArray[uvOrder[i] * 2 + j]);
            }
            else
            {
                vertex.push_back(1.f);
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

        4, 6, 0,
        0, 6, 2,

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

				1, 2, 0,
				0, 2, 3,

				1, 2, 0,
				0, 2, 3
		};

    setPolygon(vertices, verticesOrder, uv, uvIndex);
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
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);// Bind l'objet a la CG
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // Lie le buffer de data aux attribues du VAO
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex.size(), &vertex[0], GL_STATIC_DRAW); // Lie les VAOdata auVAO VAO

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, /*9*/ 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, /*9*/ 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2/*3*/, GL_FLOAT, GL_FALSE, /*9*/ 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

void Mesh::rotate(float angle, glm::vec3 vAxis)
{
    model = glm::rotate(model, angle, vAxis);
}
void Mesh::scale(glm::vec3 vScale)
{
    model =  glm::scale(model, vScale);
}
void Mesh::translate(glm::vec3 vTranslate)
{
    model = glm::translate(model, vTranslate);
}
void Mesh::resetModel()
{
    model = glm::mat4(1.f);
}

void Mesh::draw(Shader* shaderToUse, glm::mat4& projection, glm::mat4& view)
{
    shaderToUse->setMat4("model", model);
    glBindVertexArray(VAO);
    //std::cout<<vertex.size()/8<<std::endl;
    //glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, vertex.size()/8/*9*/);
    model = glm::mat4(1.f);
}

void Mesh::initVBO()
{
    // Permet de créer une zone mémoire dans la CG pour stocker le vertice;
    glGenBuffers(1, &VBO); // Genere l'ID du buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // Attribution de son type
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex.size(), &vertex[0], GL_STATIC_DRAW); // Lie les VAOdata auVAO VAO
}

void Mesh::initEBO()
{
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * indices.size(), &indices[0], GL_STATIC_DRAW);
}

uint& Mesh::getVAO()
{
    return VAO;
}

void Mesh::render(float angle, Shader &Shader, glm::mat4& projection, glm::mat4& view)
{
    for(int i = 0; i < position.size(); i++)
    {
        resetModel();
        //rotate(angle/10.f, glm::vec3(glm::cos(position[i].x), log2(position[i].y), sin(position[i].z)));
        translate(position[i] + glm::vec3(-8, -8, -8));
        scale(glm::vec3(16, 16, 16));
        //rotate(position[i].length, glm::vec3(1.f));
        draw(&Shader, projection, view);
    }
}

void Mesh::setPosition(std::vector<glm::vec3> positions)
{
    position = positions;
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}
