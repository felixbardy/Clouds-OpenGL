#ifndef DEF_SHADER
#define DEF_SHADER

#include "glad.h"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/** @class Shader
 * @brief Compile un programme de shader avec Vertex et Fragment  */
class Shader
{
    public:
    /** @brief Constructeur par défaut   */
    Shader();

    /** @brief initialise (compile et link) le shader
     * @param vertexPath string du chemin vers le fichier texte ou est stocker le shader de vertex
     * @param fragmentPath string du chemin vers le fichier texte ou est stocker le shader de fragment
     */
    void init(std::string vertexPath, std::string fragmentPath);
    /** @brief Utilise le shader pour openGL */
    void use();

    /** @brief Accesseur matrice de transformation
     * @param transformMatrix matrice 4D qui représente le repère de l'objet
    */
    void transform(glm::mat4 transformMatrix);

    /** @brief Accesseur matrice de vue
     * @param viewMatrix matrice 4D qui représente la caméra
    */
    void view(glm::mat4& viewMatrix);

    /** @brief Accesseur matrice de vue
     * @param projectionMatrix matrice 4D qui représente la caméra
    */
    void projection(glm::mat4 projectionMatrix);

    /** @brief Destructeur par défaut */
    ~Shader();

    private:
    /// Variable de référence du vertex shader
    uint vertexShader;
    /// Variable de référence du fragment shader
    uint fragmentShader;

    /// Variable de référence du programme de shader
    uint shaderProgram;

    /// String du code source du vertex shader
    const char* vertexShaderSource;
    /// String du code source du fragment shader
    const char* fragmentShaderSource;

    /// string pour récuperer le code du vertex shader
    std::string vertexCode;

    /// string pour récupérer le code du fragment shader
    std::string fragmentCode;

    /// Id de l'uniform du model
    int modelId;
    /// Id de l'uniform de vue
    int viewId;
    /// Id de l'uniform de la projection
    int projectionId;

    /// Entier représentant le succés d'une étape de compilation
    int success;

    /// Tableau ou sont stocker les rapports d'erreur en cas de compilation du shader
    char infolog[512];

    /** @brief Compile le shader de fragment */
    void compileFragment();

    /** @brief Compile le shader de vertex */
    void compileVertex();

    /** @brief Link le shader de vertex et de fragment au programme */
    void linkProgram();

    /** @brief Stock dans les variable (vertex/fragment)ShaderCodeSource 
     * @param vertexPath string chemin shader de vertex
     * @param fragmentPath string chemin shader de fragment
    */
    void readShaderFile(std::string vertexPath, std::string fragmentPath);

    /** @brief Retour d'erreur de compilation / linking des shader
     * @param Shader id du programme / shader
     * @param isLinking Met a true si on link (si non, compilation de shader)
    */
    void errorHandler(unsigned int& Shader, bool isLinking = false);

};


#endif
