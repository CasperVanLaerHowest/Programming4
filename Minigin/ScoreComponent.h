#pragma once
#include "Component.h"
class ScoreComponent :
    public dae::Component
{
public:
	ScoreComponent();
	virtual ~ScoreComponent() = default;
	virtual void FixedUpdate() override;

private:
	int m_Score{0};
	bool m_DirtyFlag = true;

	void AddScore();
};

