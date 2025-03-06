#pragma once
#include "Component.h"
class RotatorComponent :
    public dae::Component
{
public:
	RotatorComponent(float speed, float distance);
	virtual ~RotatorComponent() = default;
	virtual void Update() override;
	RotatorComponent(const RotatorComponent& other) = delete;
	RotatorComponent(RotatorComponent&& other) = delete;
	RotatorComponent& operator=(const RotatorComponent& other) = delete;
	RotatorComponent& operator=(RotatorComponent&& other) = delete;
private:
	float m_Speed;
	float m_Distance;

	float m_AccumulatedPercentage = 0.0f;
	float m_CurrentAngle = 0.0f;

};

