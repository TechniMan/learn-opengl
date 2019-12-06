//std
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
//gl
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//local
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Shader.hpp"

int screenWidth = 800, screenHeight = 600;
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    screenWidth = width;
    screenHeight = height;
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

void cleanup() {
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
    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Learning OpenGL", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "ERROR::glfwCreateWindow FAILED." << std::endl;
        cleanup();
        return 1;
    }
    glfwMakeContextCurrent(window);

    // load glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "ERROR::gladLoadGLLoader FAILED." << std::endl;
        cleanup();
        return 2;
    }

    // setup viewport
    glViewport(0, 0, screenWidth, screenHeight);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // setup shader program
    Shader basicShader("../shaders/basic.vs", "../shaders/basic.fs");
    basicShader.Use();

    // setup mesh data
    GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
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
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    GLsizei stride = 5 * sizeof(GLfloat);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // load texture
    stbi_set_flip_vertically_on_load(true);

    glActiveTexture(GL_TEXTURE0);
    GLuint texture0;
    glGenTextures(1, &texture0);
    glBindTexture(GL_TEXTURE_2D, texture0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    //float borderColour[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    //glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColour);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    GLint width0, height0, numChannels0;
    unsigned char * data0 = stbi_load("../assets/container.jpg", &width0, &height0, &numChannels0, 0);
    if (data0) {
        GLint format = GL_RGB;
        if (numChannels0 == 4) { format = GL_RGBA; }
        glTexImage2D(GL_TEXTURE_2D, 0, format, width0, height0, 0, format, GL_UNSIGNED_BYTE, data0);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "ERROR::TEXTURE::FAILED TO LOAD crate-col.png" << std::endl;
        cleanup();
        return 3;
    }
    stbi_image_free(data0);
    basicShader.SetInt("texture0", 0);

    glActiveTexture(GL_TEXTURE1);
    GLuint texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    GLint width1, height1, numChannels1;
    unsigned char * data1 = stbi_load("../assets/awesomeface.png", &width1, &height1, &numChannels1, 0);
    if (data1) {
        GLint format = GL_RGB;
        if (numChannels1 == 4) { format = GL_RGBA; }
        glTexImage2D(GL_TEXTURE_2D, 0, format, width1, height1, 0, format, GL_UNSIGNED_BYTE, data1);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "ERROR::TEXTURE::FAILED TO LOAD awesomeface.png" << std::endl;
        cleanup();
        return 3;
    }
    stbi_image_free(data1);
    basicShader.SetInt("texture1", 1);

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.39f, 0.58f, 0.93f, 1.0f);

    // The Loop
    while (!glfwWindowShouldClose(window)) {
        // update
        processInput(window);

        // rendering
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        basicShader.Use();
        basicShader.SetFloat("time", glfwGetTime());
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture0);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glBindVertexArray(VAO);
        
        glm::mat4 view(1.0f);
        view = glm::translate(view, glm::vec3(std::sin((float)glfwGetTime()), 0.0f, -3.0f));
        basicShader.SetMatrix4("view", view);
        glm::mat4 proj(1.0f);
        proj = glm::perspective(glm::radians(45.0f), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
        basicShader.SetMatrix4("proj", proj);

        for (int i = 0; i < 10; ++i) {
            glm::mat4 world(1.0f);
            world = glm::translate(world, cubePositions[i]);
            world = glm::rotate(world, (float)glfwGetTime() * glm::radians(20.0f * i), glm::vec3(1.0f, 0.3f, 0.5f));
            basicShader.SetMatrix4("world", world);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glBindVertexArray(0U);

        // end of loop
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    cleanup();
    return 0;
}
