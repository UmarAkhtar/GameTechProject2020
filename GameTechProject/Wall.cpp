#include "Wall.h"

void Wall::loadWall()
{
	vector<GLfloat> verts;
	vector<GLfloat> norms;
	vector<GLfloat> tex_coords;
	vector<GLuint> indices;
	rt3d::loadObj("cube.obj", verts, norms, tex_coords, indices);
	meshIndexCount = indices.size();
	//texture = loadBitmap("alienShipWalls.bmp");
	meshObject = rt3d::createMesh(verts.size() / 3, verts.data(), nullptr, norms.data(), tex_coords.data(), meshIndexCount, indices.data());
}

void Wall::draw()
{
	glBindTexture(GL_TEXTURE_2D, texture);
	stack.push(stack.top());
	stack.top() = glm::translate(stack.top(), pos);
	stack.top() = glm::scale(stack.top(), scale);
	rt3d::setUniformMatrix4fv(shader, "modelview", glm::value_ptr(stack.top()));
	rt3d::setMaterial(shader, material1);
	rt3d::drawIndexedMesh(meshObject, meshIndexCount, GL_TRIANGLES);
	stack.pop();
}