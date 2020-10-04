#ifndef GRAVITY_SIMULATION
#define GRAVITY_SIMULATION

#include <mutex>
#include <vector>
#include "Vector3.h"
#include "UniverseConstants.h"
#include "objects/CelestialBody.h"
#include "Renderer.h"
#include "ConsoleDisplay.h"

class Renderer;
class ConsoleDisplay;
class CelestialBody;
class UniverseConstants;

class Simulation
{

public:
	Simulation();
	
	//Manage simulated objects
	void AddCelestialBody(CelestialBody* gObject, Vector3 pos);
	void RemoveCelestialBody(int index);

	void SetOrbit(CelestialBody* target, CelestialBody* satellite, UniverseConstants* constants);

	void ResetSimulation(UniverseConstants* constants);
	void SimulateStep(UniverseConstants* constants, bool& stop);

	/// for container of CelestialBody's object pointers 
	/// calculates acceleration due to gravity
	static Vector3 CalculateAcceleration(std::vector<CelestialBody*> otherObjects, CelestialBody* target, UniverseConstants* constants);

	std::vector<CelestialBody*> Objects() const {
		return objects_;
	}

private:
	std::vector<CelestialBody*> objects_;

};

#endif