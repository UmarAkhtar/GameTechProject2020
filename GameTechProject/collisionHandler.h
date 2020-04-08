#pragma once
#include "Entity_OBB.h"
#include "Entity_Sphere.h"
#include "Ray.h"


class collisionHandler
{
	public:
		collisionHandler();
		bool checkCollision(Entity entity1, Entity entity2);
			bool checkCollisionSphereVsOBB(Entity_Sphere sphere, Entity_OBB OBB);
			bool checkCollisionSphereVsSphere(Entity_Sphere sphere1, Entity_Sphere sphere2);
			//bool checkCollisionSphereVsRay(Entity_Sphere sphere, Ray ray);
};