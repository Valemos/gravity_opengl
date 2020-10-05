#include "VectorGUI.h"

#include <GL/glew.h>

VectorGUI::VectorGUI(Vector3 color)
{
	VectorGUI::color = color;
}

void VectorGUI::SetStart(Vector3 start)
{
	pointStart = start;
}

void VectorGUI::SetEnd(Vector3 end)
{
	pointEnd = end;
}

Vector3 VectorGUI::GetStart() const
{
	return pointStart;
}

Vector3 VectorGUI::GetEnd() const
{
	return pointEnd;
}

// only setup buffer attributes
void VectorGUI::updateGlBuffer()
{
	// size is number of points in arrow times number of used coordinates
	vertexBufferSize = 4;

	delete[] vertexBuffer;  // we delete previous buffer if there was any
	vertexBuffer = new float[vertexBufferSize]();

	glGenBuffers(1, &vertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, vertexBufferSize * sizeof(float), (void*)0, GL_DYNAMIC_DRAW);

	// define two consecutive floats as one vector id 0 is the same for all figures
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
}

void VectorGUI::draw(const Renderer& renderer)
{
	// recalculate arrow points put them into buffer and draw
	int index = 0;
	// point 1
	vertexBuffer[index++] = pointStart.x;
	vertexBuffer[index++] = pointStart.y;

	// point 2
	vertexBuffer[index++] = pointEnd.x;
	vertexBuffer[index] =   pointEnd.y;

	glLineWidth(width);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, vertexBufferSize * sizeof(float), vertexBuffer, GL_DYNAMIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_LINES, 0, 2);
}
