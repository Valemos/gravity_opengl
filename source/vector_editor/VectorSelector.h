#ifndef VECTOR_SELECTION_GUI
#define VECTOR_SELECTION_GUI

#include "Vector3.h"
#include "VectorGUI.h"

class VectorSelector
{
	VectorGUI vector;
public:
	bool vectorSelected = false;

	VectorSelector();
	
	// to draw vector from certain point
	void draw(const Renderer& renderer);
	void StartSelectVector(Vector3 startPoint);
	void UpdateSelected(Vector3 endPoint);
	void FinishSelection(Vector3 endPoint);
	Vector3 GetResult() const;
};


#endif
