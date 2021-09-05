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

struct uniform
{
    int id;
    std::string name;
};

class shader
{
    public:
    shader();

    void init(std::string vertexPath, std::string fragmentPath);
    void use();

    void setUniform(std::string uniformName, float x, float y, float z, float a);
    void addUniform(std::string uniformName);
    void transform(glm::mat4 transformMatrix);

    ~shader();

    private:

    

    unsigned int vertexShader, fragmentShader, shaderProgram;
    const char* vertexShaderSource;
    const char* fragmentShaderSource;

    std::string vertexCode;
    std::string fragmentCode;

    std::vector<uniform> uniformList;

    int transformId;

    int success;
    char infolog[512];

    void compileFragment();
    void compileVertex();
    void linkProgram();
    void readShaderFile(std::string vertexPath, std::string fragmentPath);



    void errorHandler(unsigned int& shader, bool isLinking = false);
    
};


#endif