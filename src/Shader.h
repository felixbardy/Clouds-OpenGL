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
		/** @brief initialise (compile et link) le shader
     * @param vertexPath string du chemin vers le fichier texte ou est stocker le shader de vertex
     * @param fragmentPath string du chemin vers le fichier texte ou est stocker le shader de fragment
     */
    Shader(std::string vertexPath, std::string fragmentPath);


    void init(std::string vertexPath, std::string fragmentPath);
    /** @brief Utilise le shader pour openGL */
    void use();

    /** @brief Ajoute un uniform de type int
     * @param name le nom de l'uniform
     * @param value la valeur de l'uniform
     */
    void setInt(const std::string& name, int value) const;

    /** @brief Ajoute un uniform de type float
     * @param name le nom de l'uniform
     * @param value la valeur de l'uniform
     */
    void setFloat(const std::string& name, float value) const;

    /** @brief Ajoute un uniform de type vec2
     * @param name le nom de l'uniform
     * @param value la valeur de l'uniform
     */
    void setVec2(const std::string& name, const glm::vec2& value) const;

    /** @brief Ajoute un uniform de type vec2
     * @param name le nom de l'uniform
     * @param x coordonnée x du vecteur
     * @param y coordonnée y du vecteur
     */
    void setVec2(const std::string& name, float x, float y) const;

    /** @brief Ajoute un uniform de type vec3
     * @param name le nom de l'uniform
     * @param value la valeur de l'uniform
     */
    void setVec3(const std::string& name, const glm::vec3& value) const;

    /** @brief Ajoute un uniform de type vec3
     * @param name le nom de l'uniform
     * @param x coordonnée x du vecteur
     * @param y coordonnée y du vecteur
     * @param z coordonnée z du vecteur
     */
    void setVec3(const std::string& name, float x, float y, float z) const;

    /** @brief Ajoute un uniform de type vec4
     * @param name le nom de l'uniform
     * @param value la valeur de l'uniform
     */
    void setVec4(const std::string& name, const glm::vec4& value) const;

    /** @brief Ajoute un uniform de type vec4
     * @param name le nom de l'uniform
     * @param x coordonnée x du vecteur
     * @param y coordonnée y du vecteur
     * @param z coordonnée z du vecteur
     * @param w coordonnée w du vecteur
     */
    void setVec4(const std::string& name, float x, float y, float z, float w) const;

    /** @brief Ajoute un uniform de type mat2
     * @param name le nom de l'uniform
     * @param value la valeur de l'uniform
     */
    void setMat2(const std::string& name, const glm::mat2& mat) const;

    /** @brief Ajoute un uniform de type mat3
     * @param name le nom de l'uniform
     * @param value la valeur de l'uniform
     */
    void setMat3(const std::string& name, const glm::mat3& mat) const;

    /** @brief Ajoute un uniform de type mat4
     * @param name le nom de l'uniform
     * @param value la valeur de l'uniform
     */
    void setMat4(const std::string& name, const glm::mat4& mat) const;

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
