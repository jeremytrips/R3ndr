#pragma once
#include <glad/glad.h>

#include <string>
#include <GLFW/glfw3.h>

class Window{

public:
    Window(int width, int height, std::string title);

    GLFWwindow* getWindow(){
        return m_window;
    }

private:
    GLFWwindow* m_window;
    int m_width;
    int m_height;
    std::string m_title;
};