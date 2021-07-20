#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

#include "Camera_s.h"
#include "Shader_s.h"

static const int width = 800;
static const int height = 600;
static void processInput(GLFWwindow* window, float deltaTime);
static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
static void setVAO(unsigned int* vao);

Camera myCamera(glm::vec3(0.0, 0.0, 3.0));
static float deltaTime = 0.0;
int basicLighting()
{
    std::cout << "02_BasicLighting" << std::endl;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(width, height, "Learn OpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create OPENGL window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);    

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -2;
    }

    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    Shader myShader("02_02BasicLighting.vs", "02_02BasicLighting.fs");
    //myShader.use();
    Shader lightShader("02_02BasicLightingLight.vs", "02_02BasicLightingLight.fs");
    
    glm::mat4 model = glm::mat4(1.0f);
    //model = glm::rotate(model, glm::radians(25.0f), glm::vec3(0.0, 0.0, 1.0));
   /* model = glm::rotate(model, 3.14f/2.0f, glm::vec3(0.0, 0.0, 1.0));
    glm::mat4 view = myCamera.GetViewMatrix();
    glm::mat4 prj = glm::perspective(glm::radians(myCamera.Zoom), (float) width / (float) height, 0.1f, 100.f);
    myShader.setTransformMat4("model", model);
    myShader.setTransformMat4("view", view);
    myShader.setTransformMat4("prj", prj);*/
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 prj = glm::mat4(1.0f);
    unsigned int VAO;
    setVAO(&VAO);
    unsigned int lightVAO;
    setVAO(&lightVAO);

    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
    glEnable(GL_DEPTH_TEST);
    float lastTime = 0;
    while (!glfwWindowShouldClose(window))
    {
        float currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        processInput(window, deltaTime);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        view = myCamera.GetViewMatrix();        
        prj = glm::perspective(glm::radians(myCamera.Zoom), (float) width / (float) height, 0.1f, 100.f);
        myShader.use();
        model = glm::mat4(1.0f);
        myShader.setTransformMat4("model", model);
        myShader.setTransformMat4("view", view);
        myShader.setTransformMat4("prj", prj);   
        myShader.setVec3("lightColor", 1.0, 1.0, 1.0);
        myShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);    
        myShader.setVec3("lightPos", lightPos);
        myShader.setVec3("viewPos", myCamera.Position);
        
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        lightShader.use();
        
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
        
        lightShader.setTransformMat4("model", model);
        lightShader.setTransformMat4("view", view);
        lightShader.setTransformMat4("prj", prj);
        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

static void processInput(GLFWwindow* window, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        myCamera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        myCamera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        myCamera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        myCamera.ProcessKeyboard(RIGHT, deltaTime);
    }
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

static void setVAO(unsigned int* vao)
{
    glGenVertexArrays(1, vao);
    glBindVertexArray(*vao);

    float vertexs[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexs), vertexs, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

static float lastX = width/2;
static float lastY = height/2;
static bool bFirst = true;
static void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) != GLFW_PRESS)
    {
        bFirst = true;
        return;
    }
    if (bFirst)
    {
        lastX = xpos;
        lastY = ypos;
        bFirst = false;
    }
    //myCamera.ProcessMouseMovement(xpos - lastX, ypos - lastY);
    myCamera.ProcessMouseMovement(xpos - lastX, lastY - ypos);
    lastX = xpos;
    lastY = ypos;
}

static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    myCamera.ProcessMouseScroll(yoffset);
}