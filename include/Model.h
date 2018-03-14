#ifndef __MODEL_H__
#define __MODEL_H__

#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Shader.h"
#include "Mesh.h"

class Model {
public:
    Model(char* path);
    virtual void draw(Shader* shader);

private:

    std::vector<Mesh*> mChildren;
    std::vector<Texture> mTextureLoaded;
    std::string directory;

    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh* processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

};

#endif // !__MODEL_H__
