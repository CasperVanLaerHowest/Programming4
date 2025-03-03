#pragma once
#include "Component.h"
#include "TextRenderer.h"
class FpsComponent :
    public dae::Component
{
public:
	FpsComponent();
	virtual ~FpsComponent() = default;
	virtual void Update() override;
	//virtual void Render();
	//virtual void FixedUpdate() override;
	//virtual void LateUpdate() override;
	std::string GetFps() const { return m_Fps; }
private:
	std::string m_Fps;

	std::string calculateFps();
};

