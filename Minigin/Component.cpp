#include "Component.h"

Component::~Component() = default;

void Component::Update() {};

std::string Component::GetName() const
{
	return Name;
}