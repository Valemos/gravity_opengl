#ifndef GRAVITY_SIMULATION_CELESTIAL_BODY
#define GRAVITY_SIMULATION_CELESTIAL_BODY

#include <iostream>
#include <vector>

#include "objects/GravityObject.h"
#include "Displayable.h"
#include "Drawable.h"
#include <glm/vec3.hpp>

class CelestialBody : public GravityObject, public Displayable, public Drawable
{
	static const int circle_points = 20;
	glm::vec3 color;

public:
	std::string name;

	CelestialBody(std::string name, Vector3 color, UniverseConstants* constants, float radius, float surfaceGravity = 0.f, float mass = 0.f);

	CelestialBody* CheckCollision(const std::vector<CelestialBody*>& bodies);

	void draw(const Renderer& renderer) override;
	void updateGlBuffer() override;
	
	void display() override;
};


#endif // !GRAVITY_SIMULATION_CELESTIAL_BODY
