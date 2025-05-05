#pragma once
#include "Observer.h"
class ScoreObserver :
	public dae::Component,
    public dae::Observer
{
public:
    ScoreObserver();
    virtual ~ScoreObserver() = default;

    virtual void onNotify(dae::GameObject& entity, dae::Event event) override;
};

