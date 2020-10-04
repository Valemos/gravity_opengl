#include "ConsoleDisplay.h"

#include <clocale>

#include "objects/CelestialBody.h"
#include "UniverseConstants.h"
#include "Simulation.h"

ConsoleDisplay::ConsoleDisplay() {
	SetConsoleOutputCP(65001);
	ConsoleDisplay::consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
}


// objects must be Displayable subclass
void ConsoleDisplay::showGameInformation(std::vector<CelestialBody*> objects, UniverseConstants* constants, std::string info, bool rewrite) const
{
	if (rewrite)
		SetConsoleCursorPosition(ConsoleDisplay::consoleHandle, COORD{ 0, 0 });

	for (CelestialBody* body : objects) {
		body->display();

		// show accelerations to other objects
		for (CelestialBody* iter : objects) {
			if (iter != body) {
				Vector3 accel = Simulation::CalculateAcceleration(objects, body, constants);
				float dist = sqrt(body->Position().distanceSquared(iter->Position()));
				printf("\nAccl to %s\tX: %.3f Y: %.3f", iter->name.c_str(), accel.x, accel.y);
				printf("\nDist to %s\t%.3f", iter->name.c_str(), dist);
			}
		}

		std::cout << std::endl;
	}

	std::cout << info << std::endl;
}
