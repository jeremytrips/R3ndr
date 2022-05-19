//
// Created by jtsidis on 18-5-22.
//

#ifndef R3NDR_CUBE_H
#define R3NDR_CUBE_H
#include <glad/glad.h>

#include "./shader.h"


class Cube {
public:
    Cube();
    ~Cube();
    void render();
    Shader shader;
private:

    unsigned int m_vao;
    unsigned int m_vbo;
};

#endif //R3NDR_CUBE_H
