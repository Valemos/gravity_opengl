#ifndef PROGRAM_SIMULATION_FUNCTIONS
#define PROGRAM_SIMULATION_FUNCTIONS

#include "ProgramFramework.h"
#include "ProgramInputHandler.h"
#include "Simulation.h"
#include "vector_editor/VectorSelector.h"

class UniverseConstants;

class SimulationProgram : public ProgramFramework
{
	int stepCount;
	int currentStep = 0;
	UniverseConstants constants;
	Simulation simulation;
	ConsoleDisplay* display;

	// set speed of one celestial body
	CelestialBody* controlledObject;
	VectorSelector* vectorSelector;
	
public:

	// if steps count equals -1, continue simulation indefinitely
	SimulationProgram(float fps, int step_count, UniverseConstants physicalConstants) : ProgramFramework(fps),
		stepCount(step_count), vectorSelector(nullptr)
	{
		constants = physicalConstants;
		simulation = Simulation();
		display = new ConsoleDisplay();
	}

	~SimulationProgram()
	{
		delete display;
		delete vectorSelector;
	}

	int Init(ProgramInputHandler*) override
	{
		simulation.ResetSimulation();

		
		// this scale defines units of measurement related to simulation objects
		constants.coordinateScale = { 1 / 1000.f, 1 / 1000.f };
		ProgramInputHandler::renderer.SetScale(constants.coordinateScale);
		
		
		auto* Sun = new CelestialBody(
			"Sun", 
			{ 250 / 255.f, 213 / 255.f, 27 / 255.f }, 
			&constants,
			200.f, 
			274.f);
		auto* Earth = new CelestialBody(
			"Earth", 
			{ 27 / 255.f, 255 / 255.f, 110 / 255.f }, 
			&constants,
			50.f, 
			9.8f);
		
		Sun->updateGlBuffer();
		Earth->updateGlBuffer();

		simulation.SetOrbit(Sun, Earth, constants);
		
		Sun->SetPosition({ 0.f, 0.f });
		Earth->SetPosition({ 500.f, 0.f });
		vectorSelector = new VectorSelector();
		vectorSelector->StartSelectVector(Earth->Position().scale(constants.coordinateScale));
		controlledObject = Earth;
		
		simulation.AddCelestialBody(Sun);
		simulation.AddCelestialBody(Earth);

		// show initial info
		display->showGameInformation(simulation.Objects(), constants, "Initial position", true);

		glClearColor(9 / 255.f, 13 / 255.f, 59 / 255.f, 1.0);
		return 0;
	}

	// return 0 if want to continue, anything else will stop loop
	int Step(ProgramInputHandler*) override
	{
		if (!vectorSelector->vectorSelected)
		{
			
			// update vector gui and wait for mouse click
			if (ProgramInputHandler::clickedPosition != nullptr)
			{
				vectorSelector->FinishSelection(ProgramInputHandler::clickedPosition->
														scale(ProgramInputHandler::renderer.GetScale()));
				
				// must scale points, collected from mouse clicks to fit in simulation coordinate system
				controlledObject->SetSpeed(vectorSelector->GetResult()
					.scaleInv(constants.coordinateScale)
					.scaleInv(ProgramInputHandler::renderer.GetScale()));
			}
			else
			{
				vectorSelector->UpdateSelected(*ProgramInputHandler::mousePosition);
			}
		}
		else
		{
			// simulate physics
			if (stepCount == -1 || currentStep < stepCount) {
				currentStep++;
			} else {
				return 1;
			}

			if (!simulation.SimulateStep(constants))
			{
				return 1;
			}
		}

		// draw objects anyway
		glClear(GL_COLOR_BUFFER_BIT);
		for (auto* object : simulation.Objects())
		{
			object->draw(ProgramInputHandler::renderer);
		}

		if (!vectorSelector->vectorSelected)
		{
			vectorSelector->draw(ProgramInputHandler::renderer);
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
