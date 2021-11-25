#ifndef MESH_H
#define MESH_H

#include "glad.h"
#include <iostream>
#include <vector>
#include "Shader.h"
#include "Textures.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/** @class Mesh
 *  @brief Classe contenant les données d'un mesh servant à être référencée par un Object
 */
class Mesh
{
private:
    std::vector<float> m_vertex;  //!< Tableau des vertices à dessinner
    std::vector<uint>  m_indices; //!< Tableau des indices
    unsigned int m_VBO;           //!< Variable de référence du Vertex Buffer Object
    unsigned int m_EBO;           //!< Variable de référence de l'Element Buffer Object
    unsigned int m_VAO;           //!< Variable de référence du Vertex Array Object

    void init();    //!< initialise le mesh pour OpenGL
    void initVBO(); //!< initialise le VBO du mesh
    void initVAO(); //!< initialise le Vertex Array Attribue 
    void initEBO(); //!< initialise l'EBO du mesh

public:
    Mesh();
    ~Mesh();

    /** @brief Accesseur Vertex Array Object
     * @return uint représentant le VAO
    */
    uint getVAO() const;
    uint getVertexCount() const;

    /** @brief remplit les vertices du mesh
     * @param vertices Vecteur contenant toutes les vertices
     * @param verticesOrder indices de l'ordre ou utiliser les vertices
     * @param uvArray Vecteur contenant toutes les uv
     * @param uvIndex Vecteur contenant les indices de l'odre ou utiliser les uvs
     * @param color Vecteur des couleurs utilisées
     * @param colorOrder Vecteur contenant les indices des couleurs (de color) a utiliser dans l'ordre
     */
    Mesh& setPolygon(
        std::vector<float> vertices,
        std::vector<uint> verticesOrder,
        std::vector<float> uvArray = {},
        std::vector<uint> uvIndex = {},
        std::vector<float> color = {},
        std::vector<uint> colorOrder = {}
    );
};

#endif //MESH_H