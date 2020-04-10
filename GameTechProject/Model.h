#pragma once

#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"
#include "Shader.h"
#include <iostream>
#include <string>
#include <vector>
//#include <map> //Do not see where this is needed, and seems to run without, including because included in tut - sonar systems github - but this one is diff from tut followed soo ??

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <fstream>
#include <sstream>



using namespace std;


unsigned int TextureFromFile(const char* path, const string& directory, bool gamma = false);

class Model {
public:

	vector<Texture> textures_loaded;
	vector<Mesh> meshes;
	string directory;
	glm::vec3 position;
	
	glm::vec3 rotation;
	bool gammaCorrection;

	Model(string const& path,bool gamma = false);

	void modelDraw(Shader shader);
	glm::vec3 getPosition()
	{
		return position;
	}
	
	glm::vec3 getRotation()
	{
		return rotation;
	}

	void setPosition(glm::vec3 pos)
	{
		position = pos;
	}
	void setRotation(glm::vec3 rot)
	{
		 rotation = rot;
	}
private:

	void loadModel(string const& path);

	void processNode(aiNode* node, const aiScene* scene);

	Mesh processMesh(aiMesh* mesh, const aiScene* scene);

	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, const string& typeName);

	
};

unsigned int TextureFromFile(const char* path, const string& directory, bool gamma);
#endif // !MODEL_H
