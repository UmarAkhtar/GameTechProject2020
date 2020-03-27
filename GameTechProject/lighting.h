#pragma once
#include <glew.h>
#include "Shader.h"

namespace lighting
{
	struct lightStruct {
		GLfloat ambient[4];
		GLfloat diffuse[4];
		GLfloat specular[4];
		GLfloat position[4];
	};

	struct materialStruct {
		GLfloat ambient[4];
		GLfloat diffuse[4];
		GLfloat specular[4];
		GLfloat shininess;
	};

	void setLight(const Shader program, const lightStruct light);
	void setLightPos(const Shader program, const GLfloat* lightPos);
	void setMaterial(const Shader program, const materialStruct material);
}