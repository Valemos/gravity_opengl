#include "ProgramInputHandler.h"

#include <thread>
#include <iostream>
#include "Renderer.h"


ProgramInputHandler* ProgramInputHandler::instance = nullptr;

Vector3 ProgramInputHandler::window_size = { 0.0, 0.0 };
Vector3 ProgramInputHandler::keyboardMoveDir = { 0.0, 0.0 };
Vector3 ProgramInputHandler::globalScale = { 1.0, 1.0, 1.0 };


ProgramInputHandler* ProgramInputHandler::getInstance(int width = 500, int height = 500)
{
	if (instance == nullptr)
	{
		instance = new ProgramInputHandler(width, height);
	}
	return instance;
}

ProgramInputHandler::ProgramInputHandler(int width, int height)
{
	renderer = Renderer();
	window_size = { static_cast<float>(width), static_cast<float>(height) };
}

int ProgramInputHandler::RunProgram(ProgramFramework* program)
{
    // create window
	int err_code = renderer.InitGraphics(
		static_cast<int>(window_size.x), 
		static_cast<int>(window_size.y)
	);

	if (err_code != 0){
        return err_code;
	}

	GLFWwindow* window = renderer.GetWindow();
	glfwSetKeyCallback(window, callbackKeyboard);
	glfwSetWindowSizeCallback(window, callbackWindowResize);

    renderer.LoadShadersFromFile();


	program->Init(this);
	program->previousUpdateTime = glfwGetTime();
	
	while (!glfwWindowShouldClose(GetWindow())) {

		glfwPollEvents();

		if ((glfwGetTime() - program->previousUpdateTime) < program->desiredUpdateTime)
		{
			continue;
		}

		program->Step(this);
		
		glfwSwapBuffers(GetWindow());
		program->previousUpdateTime = glfwGetTime();
	}

	glfwTerminate();
	return 0;
}

GLFWwindow* ProgramInputHandler::GetWindow() const
{
	return renderer.GetWindow();
}

void ProgramInputHandler::callbackKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	int key_A = glfwGetKey(window, GLFW_KEY_A);
	int key_D = glfwGetKey(window, GLFW_KEY_D);
	int key_W = glfwGetKey(window, GLFW_KEY_W);
	int key_S = glfwGetKey(window, GLFW_KEY_S);

	keyboardMoveDir = { 0, 0 };

	if (key_A == GLFW_PRESS) {
		keyboardMoveDir.x -= 1;
	}

	if (key_D == GLFW_PRESS) {
		keyboardMoveDir.x += 1;
	}

	// handle up and down
	if (key_W == GLFW_PRESS) {
		keyboardMoveDir.y += 1;
	}

	if (key_S == GLFW_PRESS) {
		keyboardMoveDir.y -= 1;
	}

	keyboardMoveDir.normalize();
}

void ProgramInputHandler::callbackWindowResize(GLFWwindow* window, int width, int height)
{
	// change global scale to keep up with new window size
	globalScale = { window_size.x / width * globalScale.x, window_size.y / width * globalScale.y };
	
	glViewport(0, 0, width, height);
	window_size = { static_cast<float>(width), static_cast<float>(height) };
}
