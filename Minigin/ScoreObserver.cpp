#include "ScoreObserver.h"
#include "TextRenderer.h"
#include "ScoreComponent.h"
#include "GameObject.h"
#include <iostream>

ScoreObserver::ScoreObserver(std::shared_ptr<dae::GameObject> scoreText)
	: m_ScoreText(scoreText)
{
}

void ScoreObserver::onNotify(dae::GameObject& entity, dae::Event event)
{
	switch (event)
	{
	case dae::Event::ADD_SCORE:
	{
		auto scoreText = m_ScoreText->GetComponent<TextRenderer>();
		if (scoreText)
		{
			scoreText->SetText("Score: " + std::to_string(entity.GetComponent<ScoreComponent>()->GetScore()));
		}
		break;
	}
	case dae::Event::PLAYER_WON:
	{
		auto scoreText = m_ScoreText->GetComponent<TextRenderer>();
		if (scoreText)
		{
			scoreText->SetText("You Won!");
		}
		break;
	}
	}
}