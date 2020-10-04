#ifndef GRAVITY_SIMULATION_CONSTANTS
#define GRAVITY_SIMULATION_CONSTANTS

class UniverseConstants
{
public:
	UniverseConstants(float gravityConstant, float timeStep) {
		UniverseConstants::gravityConstant = gravityConstant;
		UniverseConstants::timeStep = timeStep;
	}

	float gravityConstant;
	float timeStep;
};
#endif // !GRAVITY_SIMULATION_CONSTANTS
