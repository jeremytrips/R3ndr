#pragma once

#include <map>
#include <glm/glm.hpp>
#include "shader.h"

struct Character {
    unsigned int TextureID;  // ID handle of the glyph texture
    glm::ivec2   Size;       // Size of glyph
    glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Offset to advance to next glyph
};


class TextRenderer {
public:
    TextRenderer(float width, float height);
     ~TextRenderer();
    void renderText(std::string text, glm::vec2 pos, float scale=1);

    void SetProjectionMatrix(int width, int height);
private:
    std::map<char, Character> m_characters;
    Shader m_shader;
    glm::mat4x4 m_projection;
    unsigned int m_VAO;
    unsigned int m_VBO;
};
