#include "shader.h"

CShader::CShader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vertexShaderFile;
    std::ifstream fragmentShaderFile;
    vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try 
    {
        vertexShaderFile.clear();
        vertexShaderFile.open(vertexPath, std::ios::in | std::ios::binary);
        fragmentShaderFile.open(fragmentPath, std::ios::in | std::ios::binary);
        std::stringstream vertexStream, fragmentStream;
        vertexStream << vertexShaderFile.rdbuf();
        fragmentStream << fragmentShaderFile.rdbuf();
        vertexCode = vertexStream.str();
        fragmentCode = fragmentStream.str();
        vertexShaderFile.close();
        fragmentShaderFile.close();
    }
    catch(std::ifstream::failure e)
    {
        std::cout << "ERROR: CSHADER::FILE_NOT_READ_SUCCESSFULLY" << std::endl;
    }

    const char *vertexChar = vertexCode.c_str();
    std::cout << "VERTEX CODE:  " << std::endl;
    std::cout << vertexCode << std::endl;
    const char *fragmentChar = fragmentCode.c_str();
    std::cout << "FRAGMENT CODE: " << std::endl;
    std::cout << fragmentCode << std::endl;

    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexChar, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentChar, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void CShader::use()
{
    glUseProgram(ID);
}

void CShader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int) value);
}  
void CShader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void CShader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
}
void CShader::setTransformMat4(const std::string &name, glm::mat4 &trans) const
{
    unsigned int loc = glGetUniformLocation(ID, name.c_str());
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(trans));
}