#pragma once
#include "Component.h"
class FpsComponent :
    public dae::Component
{
public:
	FpsComponent() = default;
	virtual ~FpsComponent() = default;
	virtual void FixedUpdate() override;
	//virtual void Render();
	//virtual void FixedUpdate() override;
	//virtual void LateUpdate() override;
	std::string GetFps() const { return m_Fps; }
private:
	std::string m_Fps;

	std::string calculateFps();
};

