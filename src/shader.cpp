#include "shader.h"
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <iostream>

enum ShaderType {
    NO_SHADER,
    VERTEX,
    FRAGMENT
};

Shader::Shader(const char* fragmentSource, const char* vertexSource)
{
    createShaderProgram(fragmentSource, vertexSource);   
}

Shader::Shader(const std::string fileName) {
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream file(fileName);

    ShaderType shaderType = ShaderType::NO_SHADER;

    if (file.is_open()){   //checking whether the file is open
        for (std::string line; std::getline(file,line);)
        {
            // process line.
            if (line.contains("--FRAGMENT")){
                shaderType = ShaderType::FRAGMENT;
                continue;
            } else if (line.contains("--VERTEX")){
                shaderType = ShaderType::VERTEX;
                continue;
            }

            if (shaderType==ShaderType::NO_SHADER){
                continue;
            } else if (shaderType==ShaderType::FRAGMENT){
                fragmentCode += line+"\n";
            } else if (shaderType==ShaderType::VERTEX){
                vertexCode += line+"\n";
            } else {
                std::cout << "SHADER::ERROR ShaderType unhandled";
            }
            

        }
        file.close(); //close the file object.
    } else {
        std::cout << "ERROR::SHADER Unable to open file: " << fileName << std::endl;
        exit(EXIT_FAILURE);
    }
    const char* fragmentSource = fragmentCode.c_str();
    const char* vertexSource = vertexCode.c_str();
    createShaderProgram(fragmentSource, vertexSource);
}

Shader::~Shader()
{
}

void Shader::createShaderProgram(const char* fragmentSource, const char* vertexSource){
    m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
    m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_vertexShader, 1, &vertexSource, NULL);
	glCompileShader(m_vertexShader);
    checkShaderCompilation(m_vertexShader, (char*)"VERTEX");

    glShaderSource(m_fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(m_fragmentShader);
    checkShaderCompilation(m_fragmentShader, (char*)"FRAGMENT");

    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, m_vertexShader);
	glAttachShader(m_shaderProgram, m_fragmentShader);
	glLinkProgram(m_shaderProgram);

    checkProgramCompilation(m_shaderProgram);
	
    glDeleteShader(m_vertexShader);
	glDeleteShader(m_fragmentShader);  
}

void Shader::checkShaderCompilation(unsigned int shader, char* type) {
    int  success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED::" << type << "\n" << infoLog << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Shader::checkProgramCompilation(unsigned int program) {
    int success;
    char infoLog[512];
    glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(m_shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Shader::use(){
	glUseProgram(m_shaderProgram);
}

void Shader::setBool(const std::string &name, bool value) const
{         
    glUniform1i(glGetUniformLocation(m_shaderProgram, name.c_str()), (int)value); 
}
void Shader::setInt(const std::string &name, int value) const
{ 
    glUniform1i(glGetUniformLocation(m_shaderProgram, name.c_str()), value); 
}
void Shader::setFloat(const std::string &name, float value) const
{ 
    glUniform1f(glGetUniformLocation(m_shaderProgram, name.c_str()), value); 
} 

void Shader::setMat4(const std::string &name, glm::mat4 trans) const
{ 
    glUniformMatrix4fv(
        glGetUniformLocation(m_shaderProgram, name.c_str()), 
        1,
        GL_FALSE,
        glm::value_ptr(trans)
    ); 
} 
