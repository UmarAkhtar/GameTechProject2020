#pragma once
#include "Entity_Sphere.h"

class Supply_Point : public Entity_Sphere
{
private:
	bool healthOverAmmo;

public:
	Supply_Point() {}
	Supply_Point(float myRadius, float myPosX, float myPosY, float myPosZ, glm::vec3 myRot, bool myType)
	{
		radius = myRadius;
		pos.x = myPosX;
		pos.y = myPosY;
		pos.z = myPosZ;
		rot = myRot;
		healthOverAmmo = myType;
	}
	float getRadius() { return radius; }
	void setRadius(float myRadius) { radius = myRadius; }
	bool getType() { return healthOverAmmo; }
};
