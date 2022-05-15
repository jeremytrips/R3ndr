# pragma once

class Shader
{
private:
    unsigned int m_vertexShader;
    unsigned int m_fragmentShader;
    unsigned int m_shaderProgram;


public:
    Shader(const char* fragmentSource, const char* vertexSource);
    ~Shader();

    void use();
    void checkShaderCompilation(unsigned int shader);
    void checkProgramCompilation(unsigned int program);
};


