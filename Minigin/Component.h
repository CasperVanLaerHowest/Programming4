#pragma once
#include <string>

class Component
{
public:
	virtual ~Component();
	virtual void Update();

	std::string GetName() const;
private:
	std::string Name = "";
};

