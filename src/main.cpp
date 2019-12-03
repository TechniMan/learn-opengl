//std
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
//gl/glfw
#include <glad/glad.h>
#include <GLFW/glfw3.h>
//local
#include "Shader.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

bool g_wireframeMode = false;
bool g_spaceHeldDown = false;
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    else if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !g_spaceHeldDown) {
        if (g_wireframeMode) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            g_wireframeMode = false;
        }
        else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            g_wireframeMode = true;
        }
        g_spaceHeldDown = true;
    }
    else if (g_spaceHeldDown && glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
        g_spaceHeldDown = false;
    }
}

void exitProcess() {
    glfwTerminate();
}

int main(int argc, char ** args) {
    // setup GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //macOS:
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // setup display window
    GLuint windowWidth = 800;
    GLuint windowHeight = 600;
    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Learning OpenGL", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "ERROR::glfwCreateWindow FAILED." << std::endl;
        exitProcess();
        return 1;
    }
    glfwMakeContextCurrent(window);

    // load glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "ERROR::gladLoadGLLoader FAILED." << std::endl;
        exitProcess();
        return 2;
    }

    // setup viewport
    glViewport(0, 0, windowWidth, windowHeight);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // setup shader program
    Shader basicShader("../shaders/basic.vs", "../shaders/basic.fs");

    // setup triangle
    GLfloat vertices[] = {
         0.5f,  0.5f, 0.0f,  0.5f, 0.5f, 0.5f,
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f
    };
    GLushort indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    GLuint VBO;
    glGenBuffers(1, &VBO);

    GLuint EBO;
    glGenBuffers(1, &EBO);

    // vertex array object
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glClearColor(0.39f, 0.58f, 0.93f, 1.0f);

    // The Loop
    while (!glfwWindowShouldClose(window)) {
        // update
        processInput(window);

        // rendering
        glClear(GL_COLOR_BUFFER_BIT);
        basicShader.Use();
        basicShader.SetFloat("time", glfwGetTime());
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
        glBindVertexArray(0U);

        // end of loop
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
