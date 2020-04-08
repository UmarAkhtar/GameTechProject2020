#pragma once
#include "Entity.h"

class Entity_Sphere : public Entity
{
protected:
	float radius;

public:
	Entity_Sphere() {}
	Entity_Sphere(float myRadius, float myPosX, float myPosY, float myPosZ, glm::vec3 myRot)
	{
		radius = myRadius;
		pos.x = myPosX;
		pos.y = myPosY;
		pos.z = myPosZ;
		rot = myRot;
	}
	float getRadius() { return radius; }
	void setRadius(float myRadius) { radius = myRadius;	}
};