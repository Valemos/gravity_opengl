#ifndef GRAVITY_SIMULATION_CELESTIAL_BODY
#define GRAVITY_SIMULATION_CELESTIAL_BODY

#include <iostream>
#include <vector>
#include <GL/glew.h>

#include "objects/GravityObject.h"
#include "Displayable.h"
#include "Drawable.h"

class ColorRGB {
public:
	ColorRGB(int r, int g, int b) {
		ColorRGB::r = GLbyte(r);
		ColorRGB::g = GLbyte(g);
		ColorRGB::b = GLbyte(b);
	}
	~ColorRGB() {};
	
	GLbyte r;
	GLbyte g;
	GLbyte b;
};

class CelestialBody : public GravityObject, public Displayable, public Drawable
{
private:
	ColorRGB* color;

public:
	std::string name;

	CelestialBody(std::string name, ColorRGB* color, UniverseConstants* constants, float radius, float surfaceGravity = 0.f, float mass = 0.f);

	CelestialBody* CheckCollision(std::vector<CelestialBody*> bodies);

	// Inherited via Drawable
	virtual void draw() override;

	// Inherited via Displayable
	virtual void display() override;
};


#endif // !GRAVITY_SIMULATION_CELESTIAL_BODY
