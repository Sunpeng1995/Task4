#include "Mesh.h"

using namespace glm;

Mesh::Mesh(){

}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) :
  mVertices(vertices), mIndices(indices), mTextures(textures), mIndicesCount(indices.size())
{
  glGenVertexArrays(1, &mVAO);
  glGenBuffers(1, &mVBO);
  glGenBuffers(1, &mEBO);

  glBindVertexArray(mVAO);
  glBindBuffer(GL_ARRAY_BUFFER, mVBO);
  glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), &mVertices[0], GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(unsigned int), &mIndices[0], GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
  glEnableVertexAttribArray(3);

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::draw(Shader* shader) {
  unsigned int diffuseNr = 0;
  unsigned int specularNr = 0;
  unsigned int normalNr = 0;
  for (unsigned int i = 0; i < mTextures.size(); i++) {
    glActiveTexture(GL_TEXTURE0 + i);
    std::stringstream ss;
    std::string name(mTextures[i].getName());
    if (name == "texture_diffuse") ss << diffuseNr++;
    if (name == "texture_specular") ss << specularNr++;
    if (name == "texture_normal") ss << normalNr++;
    
    shader->setInt(name + ss.str(), i);
    glBindTexture(GL_TEXTURE_2D, mTextures[i].getTextureID());
  }
  glActiveTexture(GL_TEXTURE0);

  glBindVertexArray(mVAO);
  glDrawElements(GL_TRIANGLES, mIndicesCount, GL_UNSIGNED_INT, 0);
}

void Mesh::addTexture(Texture tex) {
  mTextures.push_back(tex);
}
