#pragma once
#include "Component.h"
#include "Subject.h"

class ScoreComponent :
    public dae::Component,
	public dae::Subject
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

