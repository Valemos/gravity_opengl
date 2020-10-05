#include "ProgramInputHandler.h"

#include <thread>
#include <iostream>
#include "Renderer.h"


ProgramInputHandler* ProgramInputHandler::instance = nullptr;

Vector3 ProgramInputHandler::window_size = { 0.0, 0.0 };
Renderer ProgramInputHandler::renderer = Renderer();

Vector3* ProgramInputHandler::keyboardMoveDir = new Vector3{ 0.0, 0.0 };
Vector3* ProgramInputHandler::mousePosition = new Vector3{0.0, 0.0};
Vector3* ProgramInputHandler::clickedPosition = nullptr;


ProgramInputHandler* ProgramInputHandler::getInstance(int width = 500, int height = 500)
{
	if (instance == nullptr)
	{
		instance = new ProgramInputHandler(width, height);
	}
	return instance;
}

ProgramInputHandler::~ProgramInputHandler()
{
	delete mousePosition;
	delete clickedPosition;
	delete keyboardMoveDir;
}

ProgramInputHandler::ProgramInputHandler(int width, int height)
{
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
	glfwSetCursorPosCallback(window, callbackMouseMoved);
	glfwSetMouseButtonCallback(window, callbackMouseButton);

    renderer.LoadShadersFromFile();


	program->Init(this);
	program->previousUpdateTime = glfwGetTime();
	
	while (!glfwWindowShouldClose(GetWindow())) {

		glfwPollEvents();

		if ((glfwGetTime() - program->previousUpdateTime) < program->desiredUpdateTime)
		{
			continue;
		}

		if (program->Step(this) != 0)
		{
			break;
		}
		
		glfwSwapBuffers(GetWindow());
		program->previousUpdateTime = glfwGetTime();
	}

	glfwTerminate();
	return program->Finish(this);
}

GLFWwindow* ProgramInputHandler::GetWindow()
{
	return renderer.GetWindow();
}

void ProgramInputHandler::callbackKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	int key_A = glfwGetKey(window, GLFW_KEY_A);
	int key_D = glfwGetKey(window, GLFW_KEY_D);
	int key_W = glfwGetKey(window, GLFW_KEY_W);
	int key_S = glfwGetKey(window, GLFW_KEY_S);

	*keyboardMoveDir = { 0, 0 };

	if (key_A == GLFW_PRESS) {
		keyboardMoveDir->x -= 1;
	}

	if (key_D == GLFW_PRESS) {
		keyboardMoveDir->x += 1;
	}

	// handle up and down
	if (key_W == GLFW_PRESS) {
		keyboardMoveDir->y += 1;
	}

	if (key_S == GLFW_PRESS) {
		keyboardMoveDir->y -= 1;
	}

	keyboardMoveDir->normalize();
}

void ProgramInputHandler::callbackWindowResize(GLFWwindow* window, int width, int height)
{
	// change global scale to keep up with new window size
	auto newScale = renderer.GetScale()
							.scale(window_size)
							.scaleInv(Vector3{(float)width, (float)height});
	renderer.SetScale(newScale);
	
	glViewport(0, 0, width, height);
	window_size = { static_cast<float>(width), static_cast<float>(height) };
}

void ProgramInputHandler::callbackMouseButton(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		delete clickedPosition;
		clickedPosition = new Vector3{ static_cast<float>(xpos), static_cast<float>(ypos) };
		*clickedPosition = clickedPosition->scale(renderer.GetScale());
	}
}

void ProgramInputHandler::callbackMouseMoved(GLFWwindow* window, double xpos, double ypos)
{
	*mousePosition = Vector3{ static_cast<float>(xpos), static_cast<float>(ypos) }.scale(renderer.GetScale());
}
