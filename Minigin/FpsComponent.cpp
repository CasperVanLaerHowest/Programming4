#include "FpsComponent.h"
#include "Renderer.h"
#include "Time.h"
#include <string>
//#include "TextRenderer.h"
#include "GameObject.h" // Add this include


FpsComponent::FpsComponent()
{
}

void FpsComponent::Update()
{
	m_Fps = calculateFps() + " FPS";
	this->GetOwner()->GetComponent<TextRenderer>()->SetText(m_Fps);
}

std::string FpsComponent::calculateFps()
{
	float delta = Time::GetInstance().GetDeltaTime();
	float fps = 1 / delta;

	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << fps;
	return stream.str();
}
