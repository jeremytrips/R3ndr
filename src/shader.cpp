#include "shader.h"
#include <glad/glad.h>

#include <iostream>


Shader::Shader(const char* fragmentSource, const char* vertexSource)
{
    
    m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
    m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_vertexShader, 1, &vertexSource, NULL);
	glCompileShader(m_vertexShader);
    checkShaderCompilation(m_vertexShader);

    glShaderSource(m_fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(m_fragmentShader);
    checkShaderCompilation(m_fragmentShader);

    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, m_vertexShader);
	glAttachShader(m_shaderProgram, m_fragmentShader);
	glLinkProgram(m_shaderProgram);
	
    glDeleteShader(m_vertexShader);
	glDeleteShader(m_fragmentShader);  

}

Shader::~Shader()
{
}

void Shader::checkShaderCompilation(unsigned int shader) {
    int  success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        exit(EXIT_FAILURE);
    }

}

void Shader::use(){
	glUseProgram(m_shaderProgram);
}