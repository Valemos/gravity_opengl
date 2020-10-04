#include <iostream>
#include <string>

#include "Simulation.h"
#include "UniverseConstants.h"
#include "objects/CelestialBody.h"
#include "ConsoleDisplay.h"
#include "ProgramInputHandler.h"
#include "ProgramFramework.h"
#include <cstdlib>


class TestProgram: public ProgramFramework
{
	const Vector3 direction = { 0.f, 1.f };
	const float moveSpeed = 0.1f;

	Vector3 position;


public:
	TestProgram(float fps) : ProgramFramework(fps) {}

	int Init(ProgramInputHandler* input_handler) override
	{
		// TODO: init GL buffer for object
		
		position = { -0.5f, -0.5f };

		// set background color
		glClearColor(1.0, 116 / 255.f, 0.0, 1.0);
		return 0;
	}

	int Step(ProgramInputHandler* input_handler) override
	{
		// compare with zero
		if (abs(ProgramInputHandler::keyboardMoveDir.x) > VECTOR_FLOAT_ACCURACY ||
			abs(ProgramInputHandler::keyboardMoveDir.y) > VECTOR_FLOAT_ACCURACY)
		{
			// calculate projection on direction vector
			float kbInput = direction.scalarMult(ProgramInputHandler::keyboardMoveDir);
			position += direction * moveSpeed * kbInput;
		}

		glClear(GL_COLOR_BUFFER_BIT);

		// TODO: add here drawing of one object
		// input_handler->task_figure.draw(&input_handler->renderer, position);

		std::cout << position.x << " - " << position.y << std::endl;
		return 0;
	}
};


int simulation(ProgramInputHandler* input_handler)
{
	int step_count = 1000;

	auto* constants = new UniverseConstants(0.0001f, 0.0001f);

	Simulation simulation = Simulation();

	simulation.ResetSimulation(constants);

	auto* sun = new CelestialBody("Sun", new ColorRGB(250, 213, 27), constants, 1100.f, 274.f);
	auto* earth = new CelestialBody("Earth", new ColorRGB(27, 250, 116), constants, 10.f, 9.8f);
	//CelestialBody* moon = new CelestialBody("Moon", new ColorRGB(173, 173, 173), constants, 1.62f);

	simulation.AddCelestialBody(sun, { 0.f, 0.f });
	simulation.AddCelestialBody(earth, { 100000.f, 0.f });
	//simulation.AddCelestialBody(moon, Vector2(100100.f, 0.f));

	// simulation.SetOrbit(sun, earth, constants);

	auto* display = new ConsoleDisplay();

	int fps = 10;

	
	// show initial info
	display->showGameInformation(simulation.Objects(), constants, "Initial position", true);

	bool stop_simulation = false;
	while (!(stop_simulation || glfwWindowShouldClose(input_handler->GetWindow()))) {

		simulation.SimulateStep(constants, stop_simulation);

		for(auto object : simulation.Objects())
		{
			object->draw();
		}

		display->showGameInformation(simulation.Objects(), constants, "", true);
		glfwPollEvents();
		glfwSwapBuffers(input_handler->GetWindow());
	}
	glfwTerminate();

	//if simulation stopped early, we look at final step
	display->showGameInformation(simulation.Objects(), constants, "", true);
	std::cout << "\nSimulation Finished" << std::endl;
	return 0;
}


int main(void)
{
	ProgramInputHandler* program = ProgramInputHandler::getInstance(500, 500);
    return program->RunProgram(new TestProgram(60.f));
}