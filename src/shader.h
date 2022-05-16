# pragma once
#include <string>

class Shader
{
private:
    unsigned int m_vertexShader;
    unsigned int m_fragmentShader;
    unsigned int m_shaderProgram;

    void checkShaderCompilation(unsigned int shader, char* type);
    void checkProgramCompilation(unsigned int program);
    void createShaderProgram(const char* fragmentSource, const char* vertexSource);

public:
    Shader(const char* fragmentSource, const char* vertexSource);
    Shader(const std::string fileName);
    ~Shader();

    void use();

    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
};


