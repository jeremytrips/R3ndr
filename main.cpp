
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#define STB_IMAGE_IMPLEMENTATION
#include <GLFW/glfw3.h>


#include <ft2build.h>
#include FT_FREETYPE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>

#include <filesystem>
#include <iostream>
#include <map>

#include "src/camera.h"
#include "src/line.h"
#include "src/window.h"
#include "src/shader.h"
#include "src/text_renderer.h"
#include "src/cube.h"
#include "src/cubeWithNormals.h"
#include "src/mesh.h"
#include "src/model.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

// settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;

Window win(SCR_WIDTH, SCR_HEIGHT, "R3ndr");
TextRenderer textRenderer(SCR_WIDTH, SCR_HEIGHT);


// camera
Camera camera(glm::vec3(0.0f, 0.0f, 8.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f; // time between current fra<me and last frame
float lastFrame = 0.0f;

Shader difuseLightShader(   "/Users/jt.sidis/dev/R3ndr/src/shaders/difuseLightShader.shader");
Shader lightShader(         "/Users/jt.sidis/dev/R3ndr/src/shaders/baseShader.shader");
Shader specularLightShader( "/Users/jt.sidis/dev/R3ndr/src/shaders/specularLighting.shader");


int main()
{
    // Model* test = new Model("/Users/jt.sidis/dev/R3ndr/assets/backpack/backpack.obj");

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
    
    
    Cube* lightSource = new Cube();
    // CubeWithNormal* difuseCube = new CubeWithNormal();
    // CubeWithNormal* specularCube = new CubeWithNormal();

    glm::mat4 specularModel = glm::mat4(1.0f);
    specularModel = glm::translate(specularModel, glm::vec3(-1, 0, 0));

    glm::mat4 difuseModel = glm::mat4(1.0f);
    difuseModel = glm::translate(difuseModel, glm::vec3(1, 0, 0));

    glm::vec3 lightPos(0.5f, 2.0f, 0.0f);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, lightPos);
    model = glm::scale(model, glm::vec3(0.2f)); 
    
    float a = 0;
    while (!glfwWindowShouldClose(window))
    {
        // auto currentFrame = static_cast<float>(glfwGetTime());
        // deltaTime = currentFrame - lastFrame;
        // lastFrame = currentFrame;

        // // shader.setMat4("view", camera.GetViewMatrix());
        // processInput(window);
        // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        char pos[150];
        // glm::vec3 camPos = camera.GetPosition();
        sprintf(pos, "pos: %.2f %.2f %.2f", 0.013f, 0.053f, 0.034f);
        textRenderer.renderText(pos, glm::vec2(0, 0), 0.5);

        // glm::mat4 projection =  glm::perspective(glm::radians(camera.getZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        // glm::mat4 view = camera.GetViewMatrix();
        // a = a+0.01;
        // lightPos.x = 4*cos(a);
        // lightPos.z = 4*sin(a);

        // model = glm::mat4(1.0f);
        // model = glm::translate(model, lightPos);
        // model = glm::scale(model, glm::vec3(0.2f));

        // lightShader.bind();
        // lightShader.setMat4("projection", projection);
        // lightShader.setMat4("view", view);
        // lightShader.setMat4("model", model);
        // lightSource->render();

        // difuseLightShader.bind();
        // difuseLightShader.setMat4("projection", projection);
        // difuseLightShader.setMat4("view", view);
        // difuseLightShader.setMat4("model", difuseModel);

        // difuseLightShader.setVec3("objectColor", glm::vec3(1,0,0));
        // difuseLightShader.setVec3("lightColor", glm::vec3(1,1,1));
        // difuseLightShader.setVec3("lightPos", lightPos);
        // difuseCube->render();


        // specularLightShader.bind();
        // specularLightShader.setMat4("projection", projection);
        // specularLightShader.setMat4("view", view);
        // specularLightShader.setMat4("model", specularModel);

        // specularLightShader.setVec3("objectColor", glm::vec3(1,0,0));
        // specularLightShader.setVec3("lightColor", glm::vec3(1,1,1));
        // specularLightShader.setVec3("lightPos", lightPos);
        // specularLightShader.setVec3("viewPos", camera.GetPosition());
        // specularCube->render();


        // line1->setMVP(view*projection);
        // line2->setMVP(view*projection);
        // line3->setMVP(view*projection);

        // line1->draw();
        // line2->draw();
        // line3->draw();


        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // delete line1;
    // delete line2;
    // delete line3;
    // delete lightSource;
    // delete difuseCube;
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    //     camera.ProcessKeyboard(FORWARD, deltaTime);
    // if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    //     camera.ProcessKeyboard(BACKWARD, deltaTime);
    // if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    //     camera.ProcessKeyboard(LEFT, deltaTime);
    // if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    //     camera.ProcessKeyboard(RIGHT, deltaTime);
    // if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    //     camera.ProcessKeyboard(UP, deltaTime);
    // if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    //     camera.ProcessKeyboard(DOWN, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    textRenderer.SetProjectionMatrix(static_cast<float>(width), static_cast<float>(height));
    SCR_HEIGHT = height;
    SCR_WIDTH = width;
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

    // camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    // camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
