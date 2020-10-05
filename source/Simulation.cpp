#include "Simulation.h"

#include <iostream>
#include <string>
#include <cstdlib>


Simulation::Simulation()
{
}

void Simulation::AddCelestialBody(CelestialBody* object)
{
	objects_.push_back(object);
}

void Simulation::RemoveCelestialBody(int index)
{
	objects_.erase(objects_.begin() + index);
}

void Simulation::SetOrbit(CelestialBody* target, CelestialBody* satellite, const UniverseConstants& constants)
{
	float speedModule = sqrt(constants.gravityConstant * (target->Mass() + satellite->Mass())
							/ target->Position().distanceSquared(satellite->Position()));

	Vector3 direction = target->Position().direction(satellite->Position());
	Vector3 ortVector = Vector3(-direction.y, direction.x);

	satellite->SetSpeed(ortVector * speedModule);
}

void Simulation::ResetSimulation()
{
	objects_.clear();
}

/// 1. updates objects' velocities according to gravity laws
/// 2. updates position for every simulated object
void Simulation::SimulateStep(const UniverseConstants& constants, bool& stopSimulation)
{
	for (CelestialBody* body : objects_) {
		body->UpdateSpeed(CalculateAcceleration(objects_, body, constants), constants);
		body->UpdatePosition();

		CelestialBody* collided = body->CheckCollision(objects_);
		if (collided != nullptr) {
			stopSimulation = true;
		}
	}
}

Vector3 Simulation::CalculateAcceleration(const std::vector<CelestialBody*>& otherObjects, CelestialBody* target, const UniverseConstants& constants)
{
	Vector3 accel = Vector3(0, 0);

	for (CelestialBody* object : otherObjects) {
		if (object != target) {
			float distanceSqr = object->Position().distanceSquared(target->Position());
			Vector3 direction = object->Position().direction(target->Position(), distanceSqr);
			accel += direction * (constants.gravityConstant * object->Mass() / distanceSqr);
		}
	}

	return accel;
}