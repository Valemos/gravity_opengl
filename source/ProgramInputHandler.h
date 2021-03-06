#ifndef GL_LAB1_INPUT_HANDLER
#define GL_LAB1_INPUT_HANDLER

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Vector3.h"
#include "Renderer.h"
#include "ProgramFramework.h"


class ProgramInputHandler
{
public:
	const int fps = 60;

	static Vector3* clickedPosition;
	static Vector3* mousePosition;
	static Vector3* keyboardMoveDir;
	static Renderer renderer;

	static ProgramInputHandler* getInstance(int width, int height);
	~ProgramInputHandler();

	int RunProgram(ProgramFramework*);
	static GLFWwindow* GetWindow();
	static void callbackKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void callbackWindowResize(GLFWwindow* window, int width, int height);
	static void callbackMouseButton(GLFWwindow* window, int button, int action, int mods);
	static void callbackMouseMoved(GLFWwindow* window, double xpos, double ypos);
	
private:
	static ProgramInputHandler* instance;
	ProgramInputHandler(int width, int height);

	// we store previous window size to rescale images with global scale
	static Vector3 window_size;

};


#endif // !GL_LAB1_INPUT_HANDLER
