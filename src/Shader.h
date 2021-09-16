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
    
    unsigned int vertexShader, fragmentShader, shaderProgram;
    const char* vertexShaderSource;
    const char* fragmentShaderSource;

    std::string vertexCode;
    std::string fragmentCode;

    int modelId, viewId, projectionId;

    int success;
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
