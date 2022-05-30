#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include "shader.h"

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture {
    unsigned int id;
    std::string type;
};  


class Mesh {

public:
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;
    std::vector<Texture> m_textures;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    void draw(const Shader &shader);

private:
    unsigned int m_vao, m_vbo, m_ebo;

    void setupMesh();
};