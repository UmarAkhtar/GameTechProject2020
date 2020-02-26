#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <glew.h>
#include <glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class Shader
{
public:

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

	Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);

	void use();


	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setVec2(const std::string& name, const glm::vec2& value) const;
	void setVec2(const std::string& name, float x, float y) const;
	void setVec3(const std::string& name, const glm::vec3& value) const;
	void setVec3(const std::string& name, float x, float y, float z) const;
	void setVec4(const std::string& name, const glm::vec4& value) const;
	void setVec4(const std::string& name, float x, float y, float z, float w);
	void setMat2(const std::string& name, const glm::mat2& mat) const;
	void setMat3(const std::string& name, const glm::mat3& mat) const;
	void setMat4(const std::string& name, const glm::mat4& mat) const;
	void setUniformMatrix4fv(const char* uniformName, const GLfloat* data);
	void setLightStruct(const std::string& name, const lightStruct light);
	void setMaterial(const std::string& name, const materialStruct material);
	void setLightPos(const std::string& name, const GLfloat* lightPos);

	int getId();

private:
	int id;
	void checkCompileErrors(GLuint shader, string type);
};
#endif // !SHADER_H
