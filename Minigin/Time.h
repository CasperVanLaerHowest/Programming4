#pragma once
#include "Singleton.h"

class Time final : public dae::Singleton<Time>
{
public:
	//void Update();
	float GetDeltaTime() const { return m_DeltaTime; }
	void SetDeltaTime(float deltaTime) { m_DeltaTime = deltaTime; }
private:
	float m_DeltaTime{};
};

