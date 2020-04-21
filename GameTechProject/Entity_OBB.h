#pragma once
#include "Entity.h"

class Entity_OBB : public Entity
{
private:
	float width, length, height;

public:
	Entity_OBB(float myWidth, float myLength, float myHeight, float myPosX, float myPosY, float myPosZ, glm::vec3 myRot)
	{
		width = myWidth;
		length = myLength;
		height = myHeight;
		pos.x = myPosX;
		pos.y = myPosY;
		pos.z = myPosZ;
		rot = myRot;
	}

	float getWidth() { return width; }
	float getLength() { return length; }
	float getHeight() { return height; }
	void setWidth(float myWidth) { width = myWidth; }
	void setLength(float myLength) { length = myLength; }
	void setHeight(float myHeight) { height = myHeight; }

};
