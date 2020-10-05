#ifndef GRAVITY_OBJECT
#define GRAVITY_OBJECT

class UniverseConstants;

#include "Vector3.h"

class GravityObject

{
protected:
	Vector3 position;
	Vector3 speed;
	float mass_;
	float radius;

public:

	GravityObject(float radius, float surfaceGravity, float mass, const UniverseConstants& constants);
	virtual ~GravityObject() = default;

	void UpdateSpeed(Vector3 acceleration, const UniverseConstants& constants);
	
	void UpdatePosition();
	void RevertPosition();

	void SetSpeed(Vector3 speed) {
		speed = speed;
	}

	Vector3 Speed() {
		return speed;
	}

	void SetPosition(Vector3 position) {
		GravityObject::position = position;
	}
	
	Vector3 Position() const {
		return position;
	}

	float Mass() const {
		return mass_;
	}

	float Radius() const {
		return radius;
	}
};


#endif // !GRAVITY_OBJECT
