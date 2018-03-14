#ifndef __MESH_H__
#define __MESH_H__

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Texture.h"

struct Vertex {
  glm::vec3 Position;
  glm::vec3 Normal;
  glm::vec2 TexCoords;
  glm::vec3 Tangent;
};

class Mesh {
public:
  Mesh();
  Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
  virtual void draw(Shader* shader);
  void addTexture(Texture tex);

private:
  std::vector<Vertex> mVertices;
  std::vector<unsigned int> mIndices;
  std::vector<Texture> mTextures;
  unsigned int mVAO, mVBO, mEBO;
  size_t mIndicesCount;
};

#endif // !__MESH_H__
