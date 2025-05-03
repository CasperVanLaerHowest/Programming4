#include "ScoreComponent.h"
#include "TextRenderer.h"
#include "GameObject.h" // Add this include to resolve the incomplete type error
#include <iostream>

ScoreComponent::ScoreComponent(std::string player)
	: m_Event{ player }
{
}

void ScoreComponent::FixedUpdate()
{
	if (m_DirtyFlag)
	{
		this->GetOwner()->GetComponent<TextRenderer>()->SetText("Score: " + std::to_string(m_Score));
		m_DirtyFlag = false;
	}
}

void ScoreComponent::AddScore()
{
	m_Score += 100;
	m_DirtyFlag = true;
}
