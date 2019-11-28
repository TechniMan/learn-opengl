//std
#include <iostream>
//gl/glfw/etc
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
        std::cout << "glfwCreateWindow failed." << std::endl;
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);

    // load glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "gladLoadGLLoader failed." << std::endl;
        glfwTerminate();
        return 2;
    }

    // setup viewport
    glViewport(0, 0, windowWidth, windowHeight);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glClearColor(0.39f, 0.58f, 0.93f, 1.0f);

    // The Loop
    while (!glfwWindowShouldClose(window)) {
        // update
        processInput(window);

        // rendering
        glClear(GL_COLOR_BUFFER_BIT);

        // end of loop
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
