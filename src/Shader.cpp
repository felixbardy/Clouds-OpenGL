#include "Shader.h"
void Shader::errorHandler(unsigned int& Shader, bool isLinking)
{
    if(!isLinking)
    {
        glGetShaderiv(Shader, GL_COMPILE_STATUS, &success);
    }
    else
    {
        glGetShaderiv(Shader, GL_LINK_STATUS, &success);
    }

    if(!success)
    {
        glGetShaderInfoLog(Shader, 512, NULL, infolog);
        std::string error;
        if(isLinking)
        {
            error = "ERROR LINKING SHADER PROGRAM :: ";
        }
        else if(Shader == vertexShader)
        {
            error = "ERROR COMPILING VERTEX SHADER :: ";
        }
        else
        {
            error = "ERROR COMPILING FRAGMENT SHADER :: ";
        }

        std::cerr<<error<<std::endl<<infolog<<std::endl;
    }
}

void Shader::compileVertex()
{
    vertexShader = glCreateShader(GL_VERTEX_SHADER); // Creation du Shader
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // Injection du code source du Shader
    glCompileShader(vertexShader); // Compilation du Shader
    errorHandler(vertexShader);
}

void Shader::compileFragment()
{
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    errorHandler(fragmentShader);
}

void Shader::linkProgram()
{
    shaderProgram = glCreateProgram(); // On crée le programme
    glAttachShader(shaderProgram, vertexShader); // on attache les shaders au programme
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram); // on link le Shader a la CG
    errorHandler(shaderProgram, true);
    glDeleteShader(vertexShader); // on supprime les shaders inutile
    glDeleteShader(fragmentShader);
}




Shader::Shader(std::string vertexPath, std::string fragmentPath)
{
    readShaderFile(vertexPath, fragmentPath);
    compileVertex();
    compileFragment();
    linkProgram();
}

void Shader::readShaderFile(std::string vertexPath, std::string fragmentPath)
{
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch(std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ = " <<strerror(errno) <<std::endl;
    }
    vertexShaderSource = vertexCode.c_str();
    fragmentShaderSource = fragmentCode.c_str();
}




void Shader::use()
{
    glUseProgram(shaderProgram);
}


void Shader::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
}

void Shader::setVec2(const std::string& name, const glm::vec2& value) const
{
    glUniform2fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]);
}
void Shader::setVec2(const std::string& name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(shaderProgram, name.c_str()), x, y);
}

void Shader::setVec3(const std::string& name, const glm::vec3& value) const
{
    glUniform3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]);
}
void Shader::setVec3(const std::string& name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(shaderProgram, name.c_str()), x, y, z);
}

void Shader::setVec4(const std::string& name, const glm::vec4& value) const
{
    glUniform4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]);
}
void Shader::setVec4(const std::string& name, float x, float y, float z, float w) const
{
    glUniform4f(glGetUniformLocation(shaderProgram, name.c_str()), x, y, z, w);
}

void Shader::setMat2(const std::string& name, const glm::mat2& mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const std::string& name, const glm::mat3& mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

Shader::~Shader()
{
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteProgram(shaderProgram);
}
