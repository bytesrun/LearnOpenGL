#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <cmath>
#include "shader.h"
static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void processInput(GLFWwindow* window);
static void setVAO(unsigned int* vao);


int myShader() 
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

    CShader myShader("shader.vs", "shader.fs");
    myShader.use();
    float off = -0.5f;

    while(!glfwWindowShouldClose(window)) 
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        
        glBindVertexArray(vao);

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0) + 0.5f;
        glUniform4f(glGetUniformLocation(myShader.ID, "ourColor"), 0.0f, greenValue, 0.0f, 1.0f);

        if (off > 0.51f) off = -0.5f;
        off += 0.005f;
        //std::cout << off << std::endl;
        myShader.setFloat("myPos", off);
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
    glEnableVertexAttribArray(0);  
}