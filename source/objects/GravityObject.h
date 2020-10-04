#ifndef GRAVITY_OBJECT
#define GRAVITY_OBJECT

class UniverseConstants;

#include <vector>
#include "Vector3.h"

class GravityObject

{
protected:
	Vector3 position_;
	Vector3 speed_;
	float mass_;
	float radius_;

public:

	GravityObject(float radius, float surfaceGravity, float mass, UniverseConstants* constants);
	virtual ~GravityObject() {};

	void UpdateSpeed(Vector3 acceleration, UniverseConstants* constants);
	
	void UpdatePosition();
	void RevertPosition();

	void SetSpeed(Vector3 speed) {
		speed_ = speed;
	}

	Vector3 Speed() {
		return speed_;
	}

	void SetPosition(Vector3 position) {
		position_ = position;
	}

	Vector3 Position() const {
		return position_;
	}

	float Mass() const {
		return mass_;
	}

	float Radius() const {
		return radius_;
	}
};


#endif // !GRAVITY_OBJECT
