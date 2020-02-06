#pragma once
#include "rt3d.h"
#include "rt3dObjLoader.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <stack>
#include <Windows.h>

using namespace std;
class Wall
{


public:

	Wall::Wall()
	{

	}

	Wall::Wall(stack<glm::mat4> mvstack, GLuint tex, glm::vec3 position, glm::vec3 rotation, GLuint shaderProg, glm::vec3 wallScale) {

		stack = mvstack;
		texture = tex;
		pos = position;
		rot = rotation;
		shader = shaderProg;
		scale = wallScale;

	}

	void loadWall();
  void draw();
	private:

	stack<glm::mat4> stack;
	GLuint texture;
	glm::vec3 pos;
	glm::vec3 rot;
	glm::vec3 scale;
	GLuint shader;
	GLuint meshObject;
	GLuint meshIndexCount;
	rt3d::materialStruct material1 = {
	{0.4f, 0.4f, 1.0f, 1.0f}, // ambient
	{0.8f, 0.8f, 1.0f, 1.0f}, // diffuse
	{0.8f, 0.8f, 0.8f, 1.0f}, // specular
	1.0f  // shininess
	};

};

