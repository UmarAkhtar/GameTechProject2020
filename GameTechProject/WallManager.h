#pragma once
#include "rt3d.h"
#include "rt3dObjLoader.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <stack>
#include <Windows.h>
#include "md2model.h"
using namespace std;
class WallManager
{
private:

	stack<glm::mat4> stack;
	GLuint texture;

public:

	void  loadWall();
};

