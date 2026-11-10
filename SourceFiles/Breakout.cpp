#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ResourceManager.h"
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "stb_image.h"
#include "Texture.h"
#include "SpriteRenderer.h"
#include "Game.h"



// Call back function for resizing window
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}


// Function to close window when the ESC key is pressed
void closeWindow(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}


int main()
{
    // Initialize GLFW
    glfwWindowHint(GLFW_COCOA_CHDIR_RESOURCES, GLFW_FALSE);
    glfwInit();

    // Tell GLFW which version of OpenGL we are using (3.3)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Tell GLFW we are using the CORE profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Apple deprecated older OpenGL functionality and requires forward-compatible 
    // contexts for OpenGL 3.2 and later in its core-profile implementation
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    
    // Creates the window object
    GLFWwindow* gameWindow = glfwCreateWindow(800, 600, "BREAKOUT", NULL, NULL);

    if(gameWindow == NULL)
    {
        std::cerr << "Failed to create GLFW Window \n";
        glfwTerminate();
        return -1;
    }

    // Bring window into current context
    glfwMakeContextCurrent(gameWindow);

    // Load GLAD so it configures OpenGL
    gladLoadGL();


    // registering call back function for resizing window
    glfwSetFramebufferSizeCallback(gameWindow, framebuffer_size_callback);

    // Specify the viewport of OpenGL in the Window
    // Get the actual framebuffer dimensions to account for Retina/high-DPI displays
    int width, height;
    glfwGetFramebufferSize(gameWindow, &width, &height);
    glViewport(0, 0, width, height);
    Game Breakout(width/2 , height/2); // (division by 2 for tutorial following purposes)
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Breakout.Init();
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

     while (!glfwWindowShouldClose(gameWindow))
    {
        closeWindow(gameWindow);
        // calculate delta time
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();

        // manage user input
        // -----------------
        Breakout.ProcessInput(deltaTime);

        // update game state
        // -----------------
        Breakout.Update(deltaTime);

        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        Breakout.Render();

        glfwSwapBuffers(gameWindow);
    }

    // delete all resources as loaded using the resource manager
    ResourceManager::Clear();
    glfwDestroyWindow(gameWindow);
    glfwTerminate();
    return 0;
}


