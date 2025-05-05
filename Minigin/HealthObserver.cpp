#include "HealthObserver.h"
#include "TextRenderer.h"
#include "HealthComponent.h"

HealthObserver::HealthObserver()
{
}

void HealthObserver::onNotify(dae::GameObject& entity, dae::Event event)
{
	switch (event)
	{
		case dae::Event::TAKE_DAMAGE:
		{
			this->GetOwner()->GetComponent<TextRenderer>()
				->SetText("Health: " + std::to_string(entity.GetComponent<HealthComponent>()
					->GetHealth()));
			break;
		}
		case dae::Event::PLAYER_DEAD:
		{
			this->GetOwner()->GetComponent<TextRenderer>()
				->SetText("Player Dead");
			break;
		}
	}
}