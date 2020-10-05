#ifndef VECTOR_SELECTION_GUI
#define VECTOR_SELECTION_GUI

#include "Vector3.h"
#include "VectorGUI.h"

class VectorSelector
{
	VectorGUI* vector;
	
public:
	bool vectorSelected = false;

	VectorSelector();
	~VectorSelector();
	
	// to draw vector from certain point
	void draw(const Renderer& renderer) const;
	void StartSelectVector(Vector3 startPoint);
	void UpdateSelected(Vector3 endPoint) const;
	void FinishSelection(Vector3 endPoint);
	Vector3 GetResult() const;
};


#endif
