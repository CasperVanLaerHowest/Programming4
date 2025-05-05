#include "ScoreComponent.h"
#include "TextRenderer.h"
#include "GameObject.h" // Add this include to resolve the incomplete type error
#include <iostream>

ScoreComponent::ScoreComponent()
{
}

void ScoreComponent::FixedUpdate()
{
	if (m_DirtyFlag)
	{
		if (m_Score >= 1000)
		{
			this->Notify(*GetOwner(), dae::Event::PLAYER_WON);
			//this->GetOwner()->Notify(dae::Event::PLAYER_WON);
		}
		m_DirtyFlag = false;
	}
}

void ScoreComponent::AddScore()
{
	m_Score += 100;
	this->Notify(*GetOwner(), dae::Event::ADD_SCORE);
	//this->GetOwner()->Notify(dae::Event::ADD_SCORE);
	m_DirtyFlag = true;
}
