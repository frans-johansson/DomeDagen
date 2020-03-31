#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "model.hpp"
#include "mesh.hpp"
#include "glm/glm.hpp"
#include "glad/glad.h"
#include "utility.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <stb_image.h>

unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);

class Model
{
public:
	Model() = default;
	//Ctor with path to .fbx file
	Model(char* path);

	//Render model
	void render() const;

private:
	//Model data
	std::vector<Mesh> mMeshes;
	std::string mDirectory;

	//Load model and sets mDirectory
	void loadModel(const std::string& path);

	//Process all nodes from assimp recursively, property of online tutorial
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};