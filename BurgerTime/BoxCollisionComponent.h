#pragma once
#include "Component.h"

class BoxCollisionComponent : public dae::Component
{
public:
	BoxCollisionComponent(float width, float height);
	virtual ~BoxCollisionComponent() = default;

	float GetWidth() const { return m_Width; }
	float GetHeight() const { return m_Height; }
private:
	float m_Width;
	float m_Height;
};

