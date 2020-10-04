#include "CelestialBody.h"

#include "Vector3.h"

CelestialBody::CelestialBody(const std::string name, ColorRGB* color, UniverseConstants* constants, float radius, float surfaceGravity, float mass) :
	GravityObject(radius, surfaceGravity, mass, constants)
{
	CelestialBody::name = name;
	CelestialBody::color = color;
}

CelestialBody* CelestialBody::CheckCollision(std::vector<CelestialBody*> bodies)
{
	// we check for collision with any object
	for (auto body : bodies) {
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

void CelestialBody::draw()
{
	// TODO: rewrite draw function

	static const int circle_points = 100;
	static const float angleStep = 2.0f * 3.14159265f / circle_points;

	glBegin(GL_POLYGON);
	glColor3b(CelestialBody::color->r, CelestialBody::color->g, CelestialBody::color->b);
	double angle = 0.0;
	int i;
	for (i = 0; i < circle_points; i++)
	{
		glVertex2d(radius_ * cos(angle), radius_ * sin(angle));
		angle += angleStep;
	}
	glEnd();
}

void CelestialBody::display()
{
	printf("\n-----------\n%s\n-----------\nPos:\tX: %.1f\tY: %.1f\nSpd:\tX: %.2f\tY: %.2f\n", 
		this->name.c_str(),
		this->Radius(),
		this->Position().x,
		this->Position().y,
		this->Speed().x,
		this->Speed().y);
}
