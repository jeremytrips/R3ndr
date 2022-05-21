
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#define STB_IMAGE_IMPLEMENTATION
#include <GLFW/glfw3.h>


#include <ft2build.h>
#include FT_FREETYPE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <filesystem>
#include <iostream>
#include <map>

#include "src/camera.h"
#include "src/line.h"
#include "src/window.h"
#include "src/shader.h"
#include "src/text_renderer.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

void RenderText(Shader &s, std::string text, float x, float y, float scale, glm::vec3 color);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Window win(SCR_WIDTH, SCR_HEIGHT, "R3ndr");
TextRenderer textRenderer(SCR_WIDTH, SCR_HEIGHT);


// camera
Camera camera(glm::vec3(0.0f, 0.0f, 1.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f; // time between current frame and last frame
float lastFrame = 0.0f;


int main()
{
    GLFWwindow *window = win.getWindow();


    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    Line* line1 = new Line(glm::vec3(0, 0, 0), glm::vec3(1, 0, 0));
    line1->setColor(glm::vec3(1, 0, 0));
    Line* line2 = new Line(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    line2->setColor(glm::vec3(0, 1, 0));
    Line* line3 = new Line(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1));
    line3->setColor(glm::vec3(0, 0, 1));
    
    while (!glfwWindowShouldClose(window))
    {
        auto currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // shader.setMat4("view", camera.GetViewMatrix());
        glm::mat4 projection = glm::perspective(glm::radians(camera.getZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();

        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        char dest_string[150];
        sprintf(dest_string, "POS: %.3f %.3f %.3f", camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
        textRenderer.renderText(dest_string, glm::vec2(25, 25), 1);

        line1->setMVP(projection * view);
        line2->setMVP(projection * view);
        line3->setMVP(projection * view);

        line1->draw();
        line2->draw();
        line3->draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    delete line1;
    delete line2;
    delete line3;
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.ProcessKeyboard(UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera.ProcessKeyboard(DOWN, deltaTime);
    std::cout << camera.GetPosition().x << " " << camera.GetPosition().y << " " << camera.GetPosition().z << std::endl;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    textRenderer.SetProjectionMatrix(static_cast<float>(width), static_cast<float>(height));
}

void mouse_callback(GLFWwindow *window, double xposIn, double yposIn)
{

    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
