#pragma once
#include "Component.h"
#include "EventManager.h"
class ScoreComponent :
    public dae::Component
{
public:
	ScoreComponent(std::string player);
	virtual ~ScoreComponent() = default;
	virtual void FixedUpdate() override;

	void ProcessEvents();
	void ListenEvent(EventManager&);
	//void WriteEvent(EventManager&);

private:
	int m_Score{0};
	bool m_DirtyFlag = true;

	std::string m_Event;
	void AddScore();
};

