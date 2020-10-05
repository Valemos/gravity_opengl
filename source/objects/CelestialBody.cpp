#include "CelestialBody.h"

#include <GL/glew.h>
#include "Renderer.h"
#include "Vector3.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

CelestialBody::CelestialBody(const std::string name, Vector3 color, UniverseConstants* constants, float radius, float surfaceGravity, float mass) :
	GravityObject(radius, surfaceGravity, mass, constants)
{
	CelestialBody::name = name;
	CelestialBody::color = {color.x, color.y, color.z};
}

CelestialBody* CelestialBody::CheckCollision(const std::vector<CelestialBody*>& bodies)
{
	// we check for collision with any object
	for (auto* body : bodies) {
		if (body != this) {
			float distance = this->Position().distance(body->Position());
			if (distance < this->Radius() + body->Radius()) {
				this->RevertPosition();
				this->SetSpeed(Vector3(0.f, 0.f));
				return body;
			}
		}
	}

	return nullptr;
}

void CelestialBody::draw(const Renderer& renderer)
{
	const unsigned int shaderProgram = renderer.getShaderProgram();
	glUseProgram(shaderProgram);

	
	// calculate transform matrix
	glm::mat4 transform = glm::mat4(1.0f);

	auto coordScale = renderer.GetScale();
	transform = glm::translate(transform, glm::vec3(position.x * coordScale.x, position.y * coordScale.y, 0.f));

	// global window scale set
	transform = glm::scale(transform, coordScale);

	
	// get variable locations from shader
	const int transformLoc = glGetUniformLocation(shaderProgram, "transform");
	const int colorLoc = glGetUniformLocation(shaderProgram, "fillColor");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
	glUniform4fv(colorLoc, 1, value_ptr(color));
	
	// enable attributes for vertex buffer
	// rebind buffers for draw
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, vertexBufferSize * sizeof(float), figureVertexBuffer, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
	glEnableVertexAttribArray(0);

	glDrawArrays(GL_POLYGON, 0, circle_points);
}

void CelestialBody::updateGlBuffer()
{
	// coordinates are relative to circle center
	
	static const double angleStep = 2.0 * 3.14159265 / circle_points;

	vertexBufferSize = circle_points * 2;

	delete[] figureVertexBuffer;  // we delete previous buffer if there was any
	figureVertexBuffer = new float[vertexBufferSize]();

	double angle = 0.0;
	int bufIterate = 0;
	for (int i = 0; i < circle_points; i++)
	{
		figureVertexBuffer[bufIterate++] = radius * (float)cos(angle);  // X coordinate
		figureVertexBuffer[bufIterate++] = radius * (float)sin(angle);  // Y coordinate
		angle += angleStep;
	}

	glGenBuffers(1, &vertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, vertexBufferSize * sizeof(float), figureVertexBuffer, GL_STATIC_DRAW);

	// define two consecutive floats as one vector id 0 is the same for all figures
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
	glEnableVertexAttribArray(0);
}

void CelestialBody::display()
{
	printf("\n-----------\n%s\n-----------\nRadius:\t%.3f\nPos:\tX: %.1f\tY: %.1f\nSpd:\tX: %.2f\tY: %.2f\n", 
		this->name.c_str(),
		this->Radius(),
		this->Position().x,
		this->Position().y,
		this->Speed().x,
		this->Speed().y);
}
