#include "GravityObject.h"
#include "UniverseConstants.h"

GravityObject::GravityObject(float radius, float surfaceGravity, float mass, UniverseConstants* constants)
{
	if (surfaceGravity != 0.f)
	{
		mass_ = surfaceGravity * radius * radius / constants->gravityConstant;
	}
	else
	{
		mass_ = mass;
	}

	GravityObject::radius = radius;
	speed = Vector3(0, 0);
	position = Vector3(0, 0);
}

void GravityObject::UpdateSpeed(Vector3 acceleration, const UniverseConstants& constants)
{
	this->speed += acceleration * constants.timeStep;
}

/// <summary>
/// this function updates object position according to current speed
/// </summary>
void GravityObject::UpdatePosition()
{
	position += speed;
}

void GravityObject::RevertPosition()
{
	position -= speed;
}
