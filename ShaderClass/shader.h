#ifndef _SHADER_H_
#define _SHADER_H_

#include <glad/glad.h>
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class CShader
{
public:
    // 程序ID
    unsigned int ID;

    // 构造器读取并构建着色器
    CShader(const GLchar* vertexPath, const GLchar* fragmentPath);
    // 使用/激活程序
    void use();
    // uniform工具函数
    void setBool(const std::string &name, bool value) const;  
    void setInt(const std::string &name, int value) const;   
    void setFloat(const std::string &name, float value) const;
    void setTransformMat4(const std::string &name, glm::mat4 &trans) const;
};

#endif
