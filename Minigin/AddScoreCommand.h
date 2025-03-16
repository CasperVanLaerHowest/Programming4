#pragma once
#include "Command.h"
#include <string>
class AddScoreCommand :
    public Command
{
public:
	AddScoreCommand(std::string player);
	virtual void Execute(bool notfirstExecute) override;

private:
	std::string m_Player;
};

