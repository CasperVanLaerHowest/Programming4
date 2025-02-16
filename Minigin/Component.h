#pragma once
#include <string>

class Component
{
public:
	virtual ~Component();
	virtual void Update();
	virtual void Render() const {}
	virtual void FixedUpdate() {}
};

