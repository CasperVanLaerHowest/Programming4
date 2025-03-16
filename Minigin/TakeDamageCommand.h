#pragma once
#include "Command.h"
#include <string>

class TakeDamageCommand :
    public Command
{
public:
	TakeDamageCommand(std::string player);
	virtual void Execute(bool notfirstExecute) override;

private:
	std::string m_Player;
};

