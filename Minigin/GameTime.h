#pragma once
#include "Singleton.h"

class GameTime final : public dae::Singleton<GameTime>
{
public:
	//void Update();
	float GetDeltaTime() const { return m_DeltaTime; }
	void SetDeltaTime(float deltaTime) { m_DeltaTime = deltaTime; }
private:
	float m_DeltaTime{};
};

