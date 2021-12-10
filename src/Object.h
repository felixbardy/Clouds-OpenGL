#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <vector>

#include "glad.h"

#include "Shader.h"
#include "Textures.h"
#include "Mesh.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


/** @class Object
 * @brief Représente un objet de la scène
 */
class Object
{
private:
  Mesh * m_mesh;
  std::string              m_shaderKey;      //!< Identifiant du shader à utiliser
  std::vector<std::string> m_texturesKeys;   //!< Identifiants des textures à utiliser
  bool                     is2D;             //!< Documentation à remplir
  bool                     has_face_culling; //!< Indique si l'objet doit cacher l'environnement

protected:
  /** @brief méthode abstraite qui doit être surchargée, permet de
   * passer les Uniforms au shader utilisé par l'objet
   * 
   * @param shaders     le gestionnaire de shaders
   * @param model       la matrice model de l'objet
   * @param view        la matrice de vue
   * @param projection  la matrice de projection
   */
  virtual void setUniforms(
    Shader& shaders,
    const glm::mat4 & model,
    const glm::mat4 & view,
    const glm::mat4 & projection
  ) = 0;

public:
    /** @brief Constructeur par défaut     */
    Object();

    /** @brief destructeur par défaut     */
    ~Object();

    /** @brief Tourne autour des axes données
     * @param angle Angle de la rotation
     * @param vAxis axes
     */
    Object& rotate(float angle, glm::vec3 vAxis);

    /** @brief Redimensionne sur les axes le mesh
     * @param vScale vecteur de redimensionnement
     */
    Object& scale(glm::vec3 vScale);

    /** @brief Déplace du vecteur donnée en paramètre dans le monde
     * @param vTranslate vecteur de translation
     */
    Object& translate(glm::vec3 vTranslate);


    Object& setFaceCulling(bool face_culling);
    bool  getFaceCulling() const;

    void setMesh(Mesh * newMesh);

    /** @brief Dessinne le mesh
     */
    void draw();

    /** @brief affiche le mesh
     * @param angle angle de rotation
     * @param shaderToUse Pointeur vers le shader a utiliser
     * @param projection matrice 4 dimension du monde
     * @param view matrice 4 dimension de vue
     */
    void render(Shader & Shader, Textures & textureManager, const glm::mat4 & view, const glm::mat4 & projection);

    /** @brief remplit les positions ou afficher le mesh
     * @param positions
     */
    Object& setPosition(glm::vec3 position);

    /** @brief remplit la clé du shader du mesh
     * @param key
     */
    Object&     setShaderKey(const std::string & shaderKey);
    std::string getShaderKey() const; //!< Renvoie l'identifiant du shader utilisé

    /** @brief remplit la clé du shader du mesh
     * @param keys vecteur de string
     */
    Object& setTextureKeys(std::vector<std::string> keys);

      /** @brief obtient la clé du shader du mesh
     * @param key
     */

    Object& setTextureTypeTo3D();
    Object& setTextureTypeTo2D();
     
    /** @brief retire les transformation     */
    Object& resetModel();


    /// Matrice 4D de repère de l'objet
    glm::mat4 m_model;
    /// Vecteur 3D de position
    glm::vec3 m_position;
};

#endif //OBJECT_H
