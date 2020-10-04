#include "Simulation.h"

#include <iostream>
#include <string>
#include <cstdlib>


Simulation::Simulation()
{
}

void Simulation::AddCelestialBody(CelestialBody* object, Vector3 pos)
{
	object->SetPosition(pos);
	Simulation::objects_.push_back(object);
}

void Simulation::RemoveCelestialBody(int index)
{
	Simulation::objects_.erase(Simulation::objects_.begin() + index);
}

void Simulation::SetOrbit(CelestialBody* target, CelestialBody* satellite, UniverseConstants* constants)
{
	float speedModule = sqrt(constants->gravityConstant * (target->Mass() + satellite->Mass())
							/ target->Position().distanceSquared(satellite->Position()));

	Vector3 direction = target->Position().direction(satellite->Position());
	Vector3 ortVector = Vector3(-direction.y, direction.x);

	satellite->SetSpeed(ortVector * speedModule);
}

void Simulation::ResetSimulation(UniverseConstants* constants)
{
	objects_.clear();
}

/// 1. updates objects' velocities according to gravity laws
/// 2. updates position for every simulated object
void Simulation::SimulateStep(UniverseConstants* constants, bool& stopSimulation)
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

Vector3 Simulation::CalculateAcceleration(std::vector<CelestialBody*> otherObjects, CelestialBody* target, UniverseConstants* constants)
{
	Vector3 accel = Vector3(0, 0);
	float distanceSqr;

	for (CelestialBody* object : otherObjects) {
		if (object != target) {
			distanceSqr = object->Position().distanceSquared(target->Position());
			Vector3 direction = object->Position().direction(target->Position(), distanceSqr);
			accel += direction * (constants->gravityConstant * object->Mass() / distanceSqr);
		}
	}

	return accel;
}