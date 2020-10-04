#include "GravityObject.h"
#include "UniverseConstants.h"

GravityObject::GravityObject(float radius, float surfaceGravity, float mass, UniverseConstants* constants)
{
	if (surfaceGravity != 0.f)
	{
		GravityObject::mass_ = surfaceGravity * radius * radius / constants->gravityConstant;
	}
	else
	{
		GravityObject::mass_ = mass;
	}

	GravityObject::radius_ = radius;
	GravityObject::speed_ = Vector3(0, 0);
	GravityObject::position_ = Vector3(0, 0);
}

void GravityObject::UpdateSpeed(Vector3 acceleration, UniverseConstants* constants)
{
	this->speed_ += acceleration * constants->timeStep;
}

/// <summary>
/// this function updates object position according to current speed
/// </summary>
void GravityObject::UpdatePosition()
{
	GravityObject::position_ += GravityObject::speed_;
}

void GravityObject::RevertPosition()
{
	GravityObject::position_ -= GravityObject::speed_;
}
