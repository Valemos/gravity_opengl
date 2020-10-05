#include "VectorSelector.h"

VectorSelector::VectorSelector() : vector(nullptr)
{
}

VectorSelector::~VectorSelector()
{
	delete vector;
}

void VectorSelector::draw(const Renderer& renderer) const
{
	vector->draw(renderer);
}

void VectorSelector::StartSelectVector(Vector3 startPoint)
{
	vector = new VectorGUI({0.0, 0.0, 0.0});
	vector->updateGlBuffer();
	vector->SetStart(startPoint);
}

void VectorSelector::UpdateSelected(Vector3 endPoint) const
{
	vector->SetEnd(endPoint);
}

void VectorSelector::FinishSelection(Vector3 endPoint)
{
	vector->SetEnd(endPoint);
	vectorSelected = true;
}

Vector3 VectorSelector::GetResult() const
{
	return vector->GetEnd() - vector->GetStart();
}
