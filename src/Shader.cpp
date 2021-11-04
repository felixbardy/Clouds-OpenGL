#include "Shader.h"
void Shader::errorHandler(unsigned int& Shader, bool isLinking)
{
    if(!isLinking)
    {
        glGetShaderiv(Shader, GL_COMPILE_STATUS, &m_success);
    }
    else
    {
        glGetShaderiv(Shader, GL_LINK_STATUS, &m_success);
    }

    if(!m_success)
    {
        glGetShaderInfoLog(Shader, 512, NULL, m_infolog);
        std::string error;
        if(isLinking)
        {
            error = "ERROR LINKING SHADER PROGRAM :: ";
        }
        else if(Shader == m_vertexShader)
        {
            error = "ERROR COMPILING VERTEX SHADER :: ";
        }
        else
        {
            error = "ERROR COMPILING FRAGMENT SHADER :: ";
        }

        std::cerr<<error<<std::endl<<m_infolog<<std::endl;
    }
}

void Shader::compileVertex()
{
    m_vertexShader = glCreateShader(GL_VERTEX_SHADER); // Creation du Shader
    glShaderSource(m_vertexShader, 1, &m_vertexShaderSource, NULL); // Injection du code source du Shader
    glCompileShader(m_vertexShader); // Compilation du Shader
    errorHandler(m_vertexShader);
}

void Shader::compileFragment()
{
    m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(m_fragmentShader, 1, &m_fragmentShaderSource, NULL);
    glCompileShader(m_fragmentShader);
    errorHandler(m_fragmentShader);
}

void Shader::linkProgram(const std::string & programKey)
{
    m_programId.insert({programKey, 0});
    m_programId[programKey] = glCreateProgram(); // On crée le programme
    glAttachShader(m_programId[programKey], m_vertexShader); // on attache les shaders au programme
    glAttachShader(m_programId[programKey], m_fragmentShader);
    glLinkProgram(m_programId[programKey]); // on link le Shader a la CG
    errorHandler(m_programId[programKey], true);
    glDeleteShader(m_vertexShader); // on supprime les shaders inutile
    glDeleteShader(m_fragmentShader);
}




Shader::Shader()
{
    std::cout<<"Initialisation code Shader"<<std::endl;

    m_vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "out vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "   ourColor = aColor;\n"
    "}\0";

    m_fragmentShaderSource =

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
        m_vertexCode   = vShaderStream.str();
        m_fragmentCode = fShaderStream.str();
    }
    catch(std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ = " <<strerror(errno) <<std::endl;
    }
    m_vertexShaderSource = m_vertexCode.c_str();
    m_fragmentShaderSource = m_fragmentCode.c_str();
}









void Shader::init(const std::string & programKey, const std::string & vertexPath, const std::string & fragmentPath)
{
    readShaderFile(vertexPath, fragmentPath);
    compileVertex();
    compileFragment();
    linkProgram(programKey);
}


void Shader::use(const std::string & programKey)
{
    glUseProgram(m_programId[programKey]);
}


void Shader::setInt(const std::string & programKey, const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(m_programId.at(programKey), name.c_str()), value);
}

void Shader::setFloat(const std::string & programKey, const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(m_programId.at(programKey), name.c_str()), value);
}

void Shader::setiVec2(const std::string & programKey, const std::string& name, const glm::ivec2& value) const
{
    glUniform2iv(glGetUniformLocation(m_programId.at(programKey), name.c_str()), 1, &value[0]);
}

void Shader::setVec2(const std::string & programKey, const std::string& name, const glm::vec2& value) const
{
    glUniform2fv(glGetUniformLocation(m_programId.at(programKey), name.c_str()), 1, &value[0]);
}
void Shader::setVec2(const std::string & programKey, const std::string& name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(m_programId.at(programKey), name.c_str()), x, y);
}

void Shader::setVec3(const std::string & programKey, const std::string& name, const glm::vec3& value) const
{
    glUniform3fv(glGetUniformLocation(m_programId.at(programKey), name.c_str()), 1, &value[0]);
}
void Shader::setVec3(const std::string & programKey, const std::string& name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(m_programId.at(programKey), name.c_str()), x, y, z);
}

void Shader::setVec4(const std::string & programKey, const std::string& name, const glm::vec4& value) const
{
    glUniform4fv(glGetUniformLocation(m_programId.at(programKey), name.c_str()), 1, &value[0]);
}
void Shader::setVec4(const std::string & programKey, const std::string& name, float x, float y, float z, float w) const
{
    glUniform4f(glGetUniformLocation(m_programId.at(programKey), name.c_str()), x, y, z, w);
}

void Shader::setMat2(const std::string & programKey, const std::string& name, const glm::mat2& mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(m_programId.at(programKey), name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const std::string & programKey, const std::string& name, const glm::mat3& mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(m_programId.at(programKey), name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const std::string & programKey, const std::string& name, const glm::mat4& mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_programId.at(programKey), name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

Shader::~Shader()
{
    glDeleteShader(m_vertexShader);
    glDeleteShader(m_fragmentShader);

    std::map<std::string, uint>::iterator it = m_programId.begin();
    while(it != m_programId.end())
    {
        glDeleteProgram(it->second);
        it++;
    }
}
