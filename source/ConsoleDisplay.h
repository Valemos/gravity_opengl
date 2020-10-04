#ifndef GRAVITY_SIMULATION_DISPLAY
#define GRAVITY_SIMULATION_DISPLAY

class CelestialBody;
class UniverseConstants;

#include <Windows.h>
#include <iostream>
#include <vector>

class ConsoleDisplay
{
public:
	ConsoleDisplay();
	~ConsoleDisplay() {};

	void showGameInformation(std::vector<CelestialBody*> objects, UniverseConstants* constants, std::string info, bool rewrite) const;

private:
	HANDLE consoleHandle;
};

#endif // !DISPLAY
