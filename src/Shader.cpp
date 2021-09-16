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




Shader::Shader()
{
    std::cout<<"Initialisation code Shader"<<std::endl;

    vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "out vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "   ourColor = aColor;\n"
    "}\0";

    fragmentShaderSource =

    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "    FragColor = vec4(ourColor, 1.0);\n"
    "}\0";
    std::cout<<"Fin initialisation code Shader"<<std::endl;
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
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    vertexShaderSource = vertexCode.c_str();
    fragmentShaderSource = fragmentCode.c_str();
}

void Shader::init(std::string vertexPath, std::string fragmentPath)
{
    readShaderFile(vertexPath, fragmentPath);
    compileVertex();
    compileFragment();
    linkProgram();
    modelId = glGetUniformLocation(shaderProgram, "model");
    projectionId = glGetUniformLocation(shaderProgram, "projection");
    viewId = glGetUniformLocation(shaderProgram, "view");

}

void Shader::transform(glm::mat4 transformMatrix)
{
    glUniformMatrix4fv(modelId, 1, GL_FALSE, glm::value_ptr(transformMatrix));
}

void Shader::view(glm::mat4& viewMatrix)
{
    glUniformMatrix4fv(viewId, 1, GL_FALSE, &viewMatrix[0][0]);
}

void Shader::projection(glm::mat4 projectionMatrix)
{
    glUniformMatrix4fv(projectionId, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
}

void Shader::use()
{
    glUseProgram(shaderProgram);
}

void Shader::addUniform(std::string uniformName)
{
    uniform u;
    u.id = glGetUniformLocation(shaderProgram, uniformName.c_str());
    u.name = uniformName;
    uniformList.push_back(u);
}

void Shader::setUniform(std::string uniformName, float x, float y, float z, float a)
{
    uniform u;
    int i = 0;
    bool isMissing = false;
    while(uniformList[i].name != uniformName)
    {
        if(i >= uniformList.size())
        {
            std::cerr<<"ERREUR UNIFORM INTROUVABLE"<<std::endl;
            isMissing = true;
            break;
        }
        i++;
    }
    if(!isMissing)
    {
        glUniform4f(uniformList[i].id, x, y, z, a);
    }
}


Shader::~Shader()
{
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteProgram(shaderProgram);
}
