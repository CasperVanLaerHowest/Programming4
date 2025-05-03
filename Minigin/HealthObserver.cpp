#include "HealthObserver.h"
#include "TextRenderer.h"
#include "HealthComponent.h"

HealthObserver::HealthObserver(std::shared_ptr<dae::GameObject> healthText)
	: m_HealthText(healthText)
{
}

void HealthObserver::onNotify(dae::GameObject& entity, dae::Event event)
{
	switch (event)
	{
		case dae::Event::TAKE_DAMAGE:
		{
			auto healthText = m_HealthText->GetComponent<TextRenderer>();
			if (healthText)
			{
				healthText->SetText("Health: " + std::to_string(entity.GetComponent<HealthComponent>()->GetHealth()));
			}
			break;
		}
		case dae::Event::PLAYER_DEAD:
		{
			auto healthText = m_HealthText->GetComponent<TextRenderer>();
			if (healthText)
			{
				healthText->SetText("Game Over");
			}
			break;
		}
	}
}