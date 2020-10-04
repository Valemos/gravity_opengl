#ifndef GL_LAB1_RENDERER
#define GL_LAB1_RENDERER

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <string>

struct ShaderSourceCode {
        std::string Vertex;
        std::string Fragment;
};

class Renderer
{
public:
	Renderer();

	int InitGraphics(int width, int height);
	GLFWwindow* GetWindow() const;
    void LoadShadersFromFile();
	int getShaderProgram() const;

private:
	GLFWwindow* main_window;
	unsigned int shaderProgram;

	ShaderSourceCode ParseShader(const std::string& filePath) const;
	static unsigned int InitShaders(const ShaderSourceCode& code);
	static unsigned int CompileShader(unsigned int type, const std::string& sourceCode);
};

#endif
