#include "model.h"

#include <iostream>
#include <glm/glm.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>



Model::Model(const char* path){
    loadModel(path);
}

void Model::loadModel(std::string path){
    Assimp::Importer bite;
    const aiScene* scene = bite.ReadFile(path, aiProcess_Triangulate|aiProcess_FlipUVs);

    if (!scene || scene->mFlags&AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
        std::cout << "ERROR::ASSIMP::" << bite.GetErrorString() << std::endl;
    }
    m_directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene){
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    for (unsigned int i = 0 ; i<mesh->mNumVertices ; i++){
        Vertex vertex;
        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;

        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;

        if(mesh->mTextureCoords[0]){
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        } else {
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        }

        vertices.push_back(vertex);
    }

    for (unsigned int i = 0 ; i<mesh->mNumFaces ; i ++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0 ; face.mNumIndices ; j ++) {
            indices.push_back(face.mIndices[j]);
        }
    }


    return Mesh(vertices, indices, textures);
}

void Model::processNode(aiNode* node, const aiScene* scene){
    for(int i = 0 ; i < node->mNumMeshes ; i++){
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        m_meshes.push_back(processMesh(mesh, scene));
    }
    
    for (unsigned int i = 0 ; i < node->mNumChildren ; i++){
        processNode(node->mChildren[i], scene);
    }
}

void Model::draw(const Shader shader){
    for(auto mesh: m_meshes){
        mesh.draw(shader);
    }
}