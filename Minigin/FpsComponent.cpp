#include "FpsComponent.h"
#include "GameTime.h"
#include <string>
#include "GameObject.h" 
#include "TextRenderer.h"

void FpsComponent::FixedUpdate()
{
	m_Fps = calculateFps() + " FPS";
	this->GetOwner()->GetComponent<TextRenderer>()->SetText(m_Fps);
}

std::string FpsComponent::calculateFps()
{
	float delta = GameTime::GetInstance().GetDeltaTime();
	float fps = 1 / delta;

	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << fps;
	return stream.str();
}
