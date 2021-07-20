#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void processInput(GLFWwindow* window);
static void setVAO(unsigned int* vao);
static void setShaderVertex(unsigned int& shaderVertex);
static void setShaderFragment(unsigned int& shaderFragment);

int helloTriangle() 
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL) 
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -2;
    }
    
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    unsigned int vao;
    setVAO(&vao);

    unsigned int vertexShader;
    unsigned int fragmentShader;
    setShaderVertex(vertexShader);
    setShaderFragment(fragmentShader);
    
    unsigned int shaderPrg = glCreateProgram();   
    glAttachShader(shaderPrg, vertexShader);
    glAttachShader(shaderPrg, fragmentShader);
    glLinkProgram(shaderPrg);
    char infoLog[512];
    int success;
    glGetProgramiv(shaderPrg, GL_LINK_STATUS, &success);
    if(!success) 
    {
        glGetProgramInfoLog(shaderPrg, 512, NULL, infoLog);
        std::cout << "ERROR::::SHADERPROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    glUseProgram(shaderPrg);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    while(!glfwWindowShouldClose(window)) 
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        
        glBindVertexArray(vao);

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

static void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

static void setVAO(unsigned int* vao)
{
    float vertexs[] = {-0.5f, -0.5f, 0.0f,
                       0.5f, -0.5f, 0.0f,
                       0.5f, 0.5f, 0.0f,
                       -0.5f, 0.5, 0.0f};

    glGenVertexArrays(1, vao);
    glBindVertexArray(*vao);

    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexs), vertexs, GL_STATIC_DRAW);    
    
    unsigned int indicies[] = {
        0, 1, 3
    };
    unsigned int ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*) 0);
    glad_glEnableVertexAttribArray(0);  
}

static void setShaderVertex(unsigned int& vertexShader)
{
    const char *vertexShaderSrc = "#version 330 core\n"
                        "layout (location = 0) in vec3 aPos;\n"
                        "void main()\n"
                        "{\n"
                        "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);"
                        "}\n\0";
    //unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
    glCompileShader(vertexShader);
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}
static void setShaderFragment(unsigned int& fragmentShader)
{
    const char *fragmentShaderSrc = "#version 330 core\n"
                            "out vec4 FragColor;\n"
                            "void main()\n"
                            "{\n"
                            "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                            "}\n\0";
    //unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
    glCompileShader(fragmentShader);
    int  success;
    char infoLog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}