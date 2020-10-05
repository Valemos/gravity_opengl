#ifndef GRAVITY_SIMULATION_CONSTANTS
#define GRAVITY_SIMULATION_CONSTANTS

class UniverseConstants
{
public:
	UniverseConstants(float gravityConstant = 0.01f, float timeStep = 0.01f) {
		UniverseConstants::gravityConstant = gravityConstant;
		UniverseConstants::timeStep = timeStep;
	}

	float gravityConstant;
	float timeStep;
};
#endif // !GRAVITY_SIMULATION_CONSTANTS
