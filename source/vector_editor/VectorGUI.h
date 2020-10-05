#pragma once
#include "Vector3.h"
#include "objects/Drawable.h"

class VectorGUI : public Drawable
{
	float width = 5.f;
	Vector3 color;
	Vector3 pointStart;
	Vector3 pointEnd;
public:
	VectorGUI(Vector3 color);
	
	void SetStart(Vector3 start);
	void SetEnd(Vector3 end);

	Vector3 GetStart() const;
	Vector3 GetEnd() const;
	
	void updateGlBuffer() override;
	void draw(const Renderer& renderer) override;
};

