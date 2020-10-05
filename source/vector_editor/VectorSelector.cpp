#include "VectorSelector.h"

VectorSelector::VectorSelector() : vector({ 0.0, 0.0, 0.0 })
{
}

void VectorSelector::draw(const Renderer& renderer)
{
	vector.draw(renderer);
}

void VectorSelector::StartSelectVector(Vector3 startPoint)
{
	vector.SetStart(startPoint);
}

void VectorSelector::UpdateSelected(Vector3 endPoint)
{
	vector.SetEnd(endPoint);
}

void VectorSelector::FinishSelection(Vector3 endPoint)
{
	vector.SetEnd(endPoint);
	vectorSelected = true;
}

Vector3 VectorSelector::GetResult() const
{
	return vector.GetEnd() - vector.GetStart();
}
