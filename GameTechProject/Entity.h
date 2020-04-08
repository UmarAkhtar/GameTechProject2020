#pragma once
#include <glm.hpp>

class Entity
{
protected:
	glm::vec3 rot;
public:
	glm::vec3 pos;
	Entity() {}
	Entity(float myPosX, float myPosY, float myPosZ, glm::vec3 myRot)
	{
		pos.x = myPosX;
		pos.y = myPosY;
		pos.z = myPosZ;
		rot = myRot;
	}
	float getX() { return pos.x; }
	float getY() { return pos.y; }
	float getZ() { return pos.z; }
	void setX(float myPosX) { pos.x = myPosX; return;	}
	void setY(float myPosY) { pos.y = myPosY; return;	}
	void setZ(float myPosZ) { pos.z = myPosZ; return; }
};