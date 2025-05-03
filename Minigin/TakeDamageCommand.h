#pragma once
#include "Command.h"
#include <string>
#include "GameObject.h"

class TakeDamageCommand :  
   public Command  
{  
public:  
   TakeDamageCommand(std::shared_ptr<dae::GameObject> Object);
   virtual void Execute(bool notfirstExecute) override;  

private:  
	std::shared_ptr<dae::GameObject> m_Object;
};

