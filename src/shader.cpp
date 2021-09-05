#include "shader.h"
void shader::errorHandler(unsigned int& shader, bool isLinking)
{
    if(!isLinking)
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    }
    else
    {
        glGetShaderiv(shader, GL_LINK_STATUS, &success);
    }
    
    if(!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infolog);
        std::string error;
        if(isLinking)
        {
            error = "ERROR LINKING SHADER PROGRAM :: ";
        }
        else if(shader == vertexShader)
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

void shader::compileVertex()
{
    vertexShader = glCreateShader(GL_VERTEX_SHADER); // Creation du shader
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // Injection du code source du shader
    glCompileShader(vertexShader); // Compilation du shader
    errorHandler(vertexShader);
}

void shader::compileFragment()
{
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    errorHandler(fragmentShader);
}

void shader::linkProgram()
{
    shaderProgram = glCreateProgram(); // On crée le programme
    glAttachShader(shaderProgram, vertexShader); // on attache les shaders au programme
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram); // on link le shader a la CG
    errorHandler(shaderProgram, true);
    glDeleteShader(vertexShader); // on supprime les shaders inutile
    glDeleteShader(fragmentShader);
}




shader::shader()
{
    std::cout<<"Initialisation code shader"<<std::endl;

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
    std::cout<<"Fin initialisation code shader"<<std::endl;
}

void shader::readShaderFile(std::string vertexPath, std::string fragmentPath)
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

void shader::init(std::string vertexPath, std::string fragmentPath)
{
    readShaderFile(vertexPath, fragmentPath);
    compileVertex();
    compileFragment();
    linkProgram();
    transformId = glGetUniformLocation(shaderProgram, "transform");
    
}

void shader::transform(glm::mat4 transformMatrix)
{
    glUniformMatrix4fv(transformId, 1, GL_FALSE, glm::value_ptr(transformMatrix));
}

void shader::use()
{
    glUseProgram(shaderProgram);
}

void shader::addUniform(std::string uniformName)
{
    uniform u;
    u.id = glGetUniformLocation(shaderProgram, uniformName.c_str());
    u.name = uniformName;
    uniformList.push_back(u);
}

void shader::setUniform(std::string uniformName, float x, float y, float z, float a)
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


shader::~shader()
{  
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteProgram(shaderProgram);
}


