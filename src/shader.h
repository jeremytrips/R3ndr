# pragma once
#include <string>
#include <glm/glm.hpp>

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

    unsigned int GetProgramId() {
        return m_shaderProgram;
    }

    void bind() const;
    void unBind() const;
    
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string &name, glm::mat4 trans) const;
    void setVec3(const std::string &name, glm::vec3 value) const;
};


