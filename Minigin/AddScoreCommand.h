#pragma once
#include "Command.h"
#include <string>
#include "GameObject.h"

class AddScoreCommand :
    public Command
{
public:
	AddScoreCommand(std::shared_ptr<dae::GameObject> player);
	virtual void Execute(bool notfirstExecute) override;

private:
	std::shared_ptr<dae::GameObject> m_Player;
};

