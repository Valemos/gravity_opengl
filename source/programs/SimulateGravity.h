#ifndef PROGRAM_SIMULATION_FUNCTIONS
#define PROGRAM_SIMULATION_FUNCTIONS

#include "ProgramFramework.h"
#include "ProgramInputHandler.h"
#include "Simulation.h"

class UniverseConstants;

class SimulationProgram : public ProgramFramework
{
	int stepCount;
	int currentStep = 0;
	UniverseConstants constants;
	Simulation simulation;
	ConsoleDisplay* display;

public:

	// if steps count equals -1, continue simulation indefinitely
	SimulationProgram(float fps, int step_count, UniverseConstants physicalConstants) : ProgramFramework(fps),
		stepCount(step_count)
	{
		constants = physicalConstants;
		simulation = Simulation();
		display = new ConsoleDisplay();
	}

	int Init(ProgramInputHandler*) override
	{
		simulation.ResetSimulation();

		// scale also defines units of measurement on screen
		ProgramInputHandler::renderer.SetScale({ 1 / 500.f, 1 / 500.f, 1.f });
		
		auto* sun = new CelestialBody(
			"Sun", 
			{ 250 / 255.f, 213 / 255.f, 27 / 255.f }, 
			&constants,
			200.f, 
			274.f);
		auto* earth = new CelestialBody(
			"Earth", 
			{ 27 / 255.f, 255 / 255.f, 110 / 255.f }, 
			&constants,
			50.f, 
			9.8f);
		
		sun->updateGlBuffer();
		earth->updateGlBuffer();

		
		sun->SetPosition({ 0.f, 0.f });
		earth->SetPosition({ 500.f, 0.f });
		
		simulation.AddCelestialBody(sun);
		simulation.AddCelestialBody(earth);

		// show initial info
		display->showGameInformation(simulation.Objects(), constants, "Initial position", true);

		glClearColor(9 / 255.f, 13 / 255.f, 59 / 255.f, 1.0);
		return 0;
	}

	// return 0 if want to continue, anything else will stop loop
	int Step(ProgramInputHandler*) override
	{
		if (stepCount == -1) {
			currentStep++;
		}
		else if (currentStep >= stepCount) {
			return 1;
		}
		else {
			currentStep++;
		}

		bool stopSimulation = false;
		simulation.SimulateStep(constants, stopSimulation);

		if (stopSimulation)
		{
			return 0;
		}

		glClear(GL_COLOR_BUFFER_BIT);
		for (auto* object : simulation.Objects())
		{
			object->draw(ProgramInputHandler::renderer);
		}

		display->showGameInformation(simulation.Objects(), constants, "", true);
		return 0;
	}

	int Finish(ProgramInputHandler*) override
	{
		//if simulation stopped early, we can look at final step
		display->showGameInformation(simulation.Objects(), constants, "", true);
		std::cout << "\nSimulation Finished" << std::endl;
		return 0;
	}
};

#endif
