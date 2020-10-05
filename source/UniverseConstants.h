#ifndef GRAVITY_SIMULATION_CONSTANTS
#define GRAVITY_SIMULATION_CONSTANTS

class UniverseConstants
{
public:
	UniverseConstants(float gravityConstant = 0.01f, float timeStep = 0.01f) {
		UniverseConstants::gravityConstant = gravityConstant;
		UniverseConstants::timeStep = timeStep;
		coordinateScale = { 1.0, 1.0, 1.0 };
	}

	float gravityConstant;
	float timeStep;
	Vector3 coordinateScale;
};
#endif // !GRAVITY_SIMULATION_CONSTANTS
