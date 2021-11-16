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
 * @brief Genere un maillage utilisable par openGL */

class Mesh
{
private:
  std::vector<float>       m_vertex;         //!< Tableau des vertices à dessinner
  std::string              m_shaderKey;      //!< Identifiant du shader à utiliser
  std::vector<std::string> m_texturesKeys;   //!< Identifiants des textures à utiliser
  bool                     is2D;             //!< Documentation à remplir
  bool                     has_face_culling; //!< Indique si l'objet doit cacher l'environnement
  
  unsigned int m_VAO; //!< Variable de référence du Vertex Array Object
  unsigned int m_VBO; //!< Variable de référence du Vertex Buffer Object
  unsigned int m_EBO; //!< Variable de référence de l'Element Buffer Object

public:
    /** @brief Constructeur par défaut     */
    Mesh();

    /** @brief destructeur par défaut     */
    ~Mesh();

    /** @brief Tourne autour des axes données
     * @param angle Angle de la rotation
     * @param vAxis axes
     */
    Mesh& rotate(float angle, glm::vec3 vAxis);

    /** @brief Redimensionne sur les axes le mesh
     * @param vScale vecteur de redimensionnement
     */
    Mesh& scale(glm::vec3 vScale);

    /** @brief Déplace du vecteur donnée en paramètre dans le monde
     * @param vTranslate vecteur de translation
     */
    Mesh& translate(glm::vec3 vTranslate);


    Mesh& setFaceCulling(bool face_culling);
    bool  getFaceCulling() const;

    /** @brief Dessinne le mesh
     */
    void draw();

    /** @brief affiche le mesh
     * @param angle angle de rotation
     * @param shaderToUse Pointeur vers le shader a utiliser
     * @param projection matrice 4 dimension du monde
     * @param view matrice 4 dimension de vue
     */
    void render(Shader & Shader, Textures & textureManager, const glm::mat4 & view, const glm::mat4 & projection, float angle);

    /** @brief remplit les positions ou afficher le mesh
     * @param positions
     */
    Mesh& setPosition(std::vector<glm::vec3> positions);

    /** @brief remplit la clé du shader du mesh
     * @param key
     */
    Mesh&       setShaderKey(const std::string & shaderKey);
    std::string getShaderKey() const; //!< Renvoie l'identifiant du shader utilisé

    /** @brief remplit la clé du shader du mesh
     * @param keys vecteur de string
     */
    Mesh& setTextureKeys(std::vector<std::string> keys);

      /** @brief obtient la clé du shader du mesh
     * @param key
     */

    Mesh& setTextureTypeTo3D();
    Mesh& setTextureTypeTo2D();

    /** @brief remplit les vertices du mesh
     * @param vertexArray Vecteur contenant toutes les vertices
     * @param u Vecteur contenant toutes les uv
     * @param uvIndex Vecteur contenant les indices de l'odre ou utiliser les uvs
     * @param c vecteur de couleur
     * @param indiceArray indices de l'ordre ou utiliser les vertices
     */
    Mesh& setPolygon(std::vector<float> vertices, std::vector<uint> verticesOrder, std::vector<float> uvArray = {}, std::vector<uint> uvOrder = {}, std::vector<float> color = {}, std::vector<uint> colorOrder = {});
    
    /** @brief remplit les vertices du Cube
     * @param u Vecteur contenant toutes les uv
     * @param uvIndex Vecteur contenant les indices de l'odre ou utiliser les uvs
     * @param c vecteur de couleur
     */
    Mesh& setCube();
     
    /** @brief retire les transformation     */
    Mesh& resetModel();

    /** @brief Accesseur Vertex Array Object
     * @return id uint de l'objet
    */
    uint & getVAO();

    

    /** @brief init le mesh    */
    void init();

    /// Matrice 4D de repère de l'objet
    glm::mat4 m_model;
    /// Vecteur 3D de position
    std::vector<glm::vec3> m_position;
    /// Vecteur d'indices des sommets
    std::vector<uint> m_indices;

    /** @brief init le Vertex Buffer Object    */
    void initVBO();
    /** @brief init le Vertex Array Object    */
    void initVAO();
    /** @brief init le Element Buffer Object    */
    void initEBO();

};

#endif //MESH_H
