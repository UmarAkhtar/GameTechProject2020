#include <algorithm>
#include <glm.hpp>
#include "collisionHandler.h"
using namespace std;

collisionHandler::collisionHandler() {}

bool collisionHandler::checkCollisionSphereVsOBB(Entity_Sphere sphere, Entity_OBB OBB)
{
	float cX = max(OBB.getX() - OBB.getWidth() / 2, min(sphere.getX(), OBB.getX() + OBB.getWidth() / 2));
	float cY = max(OBB.getY() - OBB.getHeight() / 2, min(sphere.getY(), OBB.getY() + OBB.getHeight() / 2));
	float cZ = max(OBB.getZ() - OBB.getLength() / 2, min(sphere.getZ(), OBB.getZ() + OBB.getLength() / 2));

	float distance = sqrt((cX - sphere.getX()) * (cX - sphere.getX()) +
		(cY - sphere.getY()) * (cY - sphere.getY()) +
		(cY - sphere.getZ()) * (cY - sphere.getZ()));

	return distance < sphere.getRadius();
}

bool collisionHandler::checkCollisionSphereVsSphere(Entity_Sphere sphere1, Entity_Sphere sphere2)
{
	float distance = sqrt((sphere1.getX() - sphere2.getX()) * (sphere1.getX() - sphere2.getX()) +
		(sphere1.getY() - sphere2.getY()) * (sphere1.getY() - sphere2.getY()) +
		(sphere1.getZ() - sphere2.getZ()) * (sphere1.getZ() - sphere2.getZ()));;

	return distance < sphere1.getRadius() + sphere2.getRadius();
}

/*bool collisionHandler::checkCollisionSphereVsRay(Entity_Sphere sphere, Ray ray)
{
	glm::vec3 spherePosition(sphere.getX(), sphere.getY(), 0);
	float spherePositionToRayPosition = spherePosition - glm::vec3(ray.getX(), ray.getY(), 0);
	float tc = dot(spherePositionToRayPosition, ray.getRot());
	
	if (tc < 0.0)
	{
		return false;
	}

	float spherePositionToClosestPointOnRay = sqrt((tc * tc) - (spherePositionToRayPosition * spherePositionToRayPosition));
	if (spherePositionToClosestPointOnRay > sphere.getRadius())
	{
		return false;
	}

	return true;
}*/