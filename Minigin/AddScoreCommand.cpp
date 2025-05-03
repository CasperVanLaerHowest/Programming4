#include "AddScoreCommand.h"
#include "InputManager.h"
#include "ScoreComponent.h"
#include <iostream>
#include "GameObject.h"

AddScoreCommand::AddScoreCommand(std::shared_ptr<dae::GameObject> player)
	: m_Player(player)
{
}

void AddScoreCommand::Execute(bool notfirstExecute)
{
	if (!notfirstExecute)
	{
		std::cout << "AddScoreCommand" << std::endl;
		m_Player->GetComponent<ScoreComponent>()->AddScore();
	}
}
