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
  bool                     is2D;             //!< Indique si les textures utilisées sont 2D
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

    /** @brief Tourne l'objet autour de l'axe donné
     * @param angle Angle de la rotation
     * @param vAxis axe
     */
    Object& rotate(float angle, glm::vec3 vAxis);

    /** @brief Redimensionne l'objet selon les axes x, y et z
     * @param vScale vecteur de redimensionnement
     */
    Object& scale(glm::vec3 vScale);

    /** @brief Déplace l'objet selon le vecteur donné
     * @param vTranslate vecteur de translation
     */
    Object& translate(glm::vec3 vTranslate);

    /** @brief Permet d'activer/désactiver le face culling pour l'objet
     * @param face_culling la valeur à donner au paramètre
     */
    Object& setFaceCulling(bool face_culling);
    /// Renvoie true si le face culling est activé pour l'objet. renvoie false sinon
    bool  getFaceCulling() const;

    virtual void setUniform(Shader & Shader, const glm::mat4 & view, const glm::mat4 & projection);

    /// Permet de changer le mesh utilisé par l'objet
    void setMesh(Mesh * newMesh);

    /** @brief Dessinne l'objet (utiliser render pour la procédure complète d'affichage)
     */
    void draw();

    /** @brief affiche l'objet
     * @param angle angle de rotation
     * @param shaderToUse Pointeur vers le shader a utiliser
     * @param projection matrice 4 dimension du monde
     * @param view matrice 4 dimension de vue
     */
    void render(Shader & Shader, Textures & textureManager, const glm::mat4 & view, const glm::mat4 & projection);

    /** @brief Remplace la position de l'objet par le vecteur donné
     * @param position la nouvelle position de l'objet
     */
    Object& setPosition(glm::vec3 position);

    /** @brief remplit la clé du shader de l'objet
     * @param key la clé du shader à utiliser
     */
    Object&     setShaderKey(const std::string & shaderKey);
    std::string getShaderKey() const; //!< Renvoie l'identifiant du shader utilisé

    /** @brief remplit les clés de textures de l'objet 
     * @param keys vecteur de string
     */
    Object& setTextureKeys(std::vector<std::string> keys);

    /// Indique à l'objrt qu'il utilise des textures 3D
    Object& setTextureTypeTo3D();
    /// Indique à l'objet qu'il utilise des textures 2D
    Object& setTextureTypeTo2D();
     
    /// Remet la matrice model à sa valeur par défaut (l'identité)
    Object& resetModel();


    /// Matrice 4D de repère de l'objet
    glm::mat4 m_model;
    /// Vecteur 3D de position
    glm::vec3 m_position;
};

#endif //OBJECT_H
