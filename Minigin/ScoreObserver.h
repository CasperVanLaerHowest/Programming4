#pragma once
#include "Observer.h"
class ScoreObserver :
    public dae::Observer
{
public:
    ScoreObserver(std::shared_ptr<dae::GameObject>);
    virtual ~ScoreObserver() = default;

    virtual void onNotify(dae::GameObject& entity, dae::Event event) override;
private:
    std::shared_ptr<dae::GameObject> m_ScoreText;
};

