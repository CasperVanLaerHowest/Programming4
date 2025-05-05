#include "ScoreObserver.h"
#include "TextRenderer.h"
#include "ScoreComponent.h"
#include "GameObject.h"
#include <iostream>

ScoreObserver::ScoreObserver()
{
}

void ScoreObserver::onNotify(dae::GameObject& entity, dae::Event event)
{
	switch (event)
	{
	case dae::Event::ADD_SCORE:
	{
		this->GetOwner()->GetComponent<TextRenderer>()
			->SetText("Score: " + std::to_string(entity.GetComponent<ScoreComponent>()
				->GetScore()));
		break;
	}
	case dae::Event::PLAYER_WON:
	{
		this->GetOwner()->GetComponent<TextRenderer>()
			->SetText("Player Won");
		break;
	}
	}
}