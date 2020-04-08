#pragma once
#include "Entity_Sphere.h"

class player : public Entity_Sphere
{
private:
	int health;
	int ammo;

public:
	player() {}
	player(float myRadius, float myPosX, float myPosY, float myPosZ, glm::vec3 myRot)
	{
		radius = myRadius;
		pos.x = myPosX;
		pos.y = myPosY;
		pos.z = myPosZ;
		rot = myRot;
		health = 100;
		ammo = 100;
	}
	float getRadius() { return radius; }
	void setRadius(float myRadius) { radius = myRadius; }
	int getHealth() { return health; }
	void setHealth(int myHealth) { health= myHealth; }
	int getAmmo() { return ammo; }
	void setAmmo(int myAmmo) { ammo = myAmmo; }
};
