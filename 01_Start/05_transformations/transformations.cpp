#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "shader.h"
#include "stb_image.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void processInput(GLFWwindow* window);
static void setVAO(unsigned int* vao);
static void setTexture(unsigned int* texture, const char* imgPath, int type = 0);
int transformations() 
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

    unsigned int texture1;
    glActiveTexture(GL_TEXTURE0);
    setTexture(&texture1, "container.jpg");
    unsigned int texture2;
    glActiveTexture(GL_TEXTURE1);
    stbi_set_flip_vertically_on_load(true);
    setTexture(&texture2, "awesomeface.png", 1);   

    CShader myShader("01_05transformations.vs", "01_05transformations.fs");
    myShader.use();
    myShader.setInt("texture1", 0);
    myShader.setInt("texture2", 1);
    
    glm::mat4 trans = glm::mat4(1.0);
    //trans = glm::translate(trans, glm::vec3(0.5f, 0.5f, 0.0f));
    //trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    double st = glfwGetTime();
    //trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));
    
    
    while(!glfwWindowShouldClose(window)) 
    {
        processInput(window);
        float angle = glfwGetTime() - st;
        trans = glm::mat4(1.0);
        trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));
        trans = glm::translate(trans, glm::vec3(0.8f * sin(angle), 0.8f * cos(angle), 0.0f));
        trans = glm::rotate(trans, glm::radians(angle * 10), glm::vec3(0.0f, 0.0f, 1.0f));
        myShader.setTransformMat4("trans", trans);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(vao);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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
    float vertexs[] = {
        //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
    };

    glGenVertexArrays(1, vao);
    glBindVertexArray(*vao);

    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexs), vertexs, GL_STATIC_DRAW);    
    
    unsigned int indicies[] = {
        0, 1, 3,
        3, 1, 2
    };
    unsigned int ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);  
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*) (3*sizeof(float)));
    glEnableVertexAttribArray(1); 
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*) (6*sizeof(float)));
    glEnableVertexAttribArray(2);
}

static void setTexture(unsigned int* texture, const char* imgPath, int type)
{
    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, *texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    int width, height, nrChannels;
    unsigned char *data = stbi_load(imgPath, &width, &height, &nrChannels, 0);

    if (data)
    {
        switch (type) 
        {
            case 0: //jpg
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                break;
            case 1: //png
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                break;
        }
        
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}
