#pragma once
#include "Component.h"
class ScoreComponent :
    public dae::Component
{
public:
	ScoreComponent();
	virtual ~ScoreComponent() = default;
	virtual void FixedUpdate() override;

	int GetScore() const { return m_Score; }
	void AddScore();

private:
	int m_Score{0};
	bool m_DirtyFlag = true;

	
};

