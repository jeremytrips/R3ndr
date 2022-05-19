//
// Created by jtsidis on 18-5-22.
//

#ifndef R3NDR_TEXTUREDCUBE_H
#define R3NDR_TEXTUREDCUBE_H

#include <string>
#include <iostream>
#include <glad/glad.h>
#include "shader.h"


class TexturedCube{
public:
    TexturedCube(std::string texturePath);
    ~TexturedCube();

    [[nodiscard]] unsigned int GetTexture() const {
        return m_texture;
    }

    void render() const;
    Shader shader;

private:
    unsigned int m_vao;
    unsigned int m_vbo;
    unsigned int m_texture;


};


#endif //R3NDR_TEXTUREDCUBE_H
