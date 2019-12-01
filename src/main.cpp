//std
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
//gl/glfw
#include <glad/glad.h>
#include <GLFW/glfw3.h>
//local

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
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

    // setup vertex shader
    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    std::ifstream vsfile("../shaders/basic.vs");
    std::stringstream vsss = std::stringstream();
    vsss << vsfile.rdbuf();
    const std::string& vertexShaderSource = vsss.str();
    const char* vss = vertexShaderSource.c_str();
    glShaderSource(vertexShader, 1, &vss, NULL);
    glCompileShader(vertexShader);
    int success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::VERTEX SHADER COMPILATION FAILED:" << std::endl << infoLog << std::endl;
        exitProcess();
        return 3;
    }

    // setup fragment shader
    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    std::ifstream file("../shaders/basic.fs");
    std::stringstream ss = std::stringstream();
    ss << file.rdbuf();
    const std::string& fragmentShaderSource = ss.str();
    const char* fss = fragmentShaderSource.c_str();
    glShaderSource(fragmentShader, 1, &fss, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "ERROR::FRAGMENT SHADER COMPILATION FAILED:" << std::endl << infoLog << std::endl;
        exitProcess();
        return 4;
    }

    // setup shader program
    GLuint shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER PROGRAM LINKING FAILED:" << std::endl << infoLog << std::endl;
        exitProcess();
        return 5;
    }
    
    // cleanup shaders
    glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // setup triangle
    GLfloat vertices[] = {
         0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glClearColor(0.39f, 0.58f, 0.93f, 1.0f);

    // The Loop
    while (!glfwWindowShouldClose(window)) {
        // update
        processInput(window);

        // rendering
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
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
