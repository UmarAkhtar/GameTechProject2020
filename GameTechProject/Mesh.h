#pragma once
#ifndef MESH_H
#define MESH_H

#include "Shader.h"
#include <glew.h>
#include <gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


using namespace std;

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
};

struct Texture
{
	unsigned int id;
	string type;
	string path;
};

class Mesh
{
public:
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;

	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
	void Draw(Shader shader);

private:
	unsigned int VBO;
	unsigned int EBO;
	unsigned int VAO;

	void setupMesh();
};

#endif // !MESH_H
