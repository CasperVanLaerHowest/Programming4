#pragma once  
#include "Observer.h"  
class HealthObserver :  
   public dae::Observer  
{  
public:  
   HealthObserver(std::shared_ptr<dae::GameObject>);  
   virtual ~HealthObserver() = default;  

   virtual void onNotify(dae::GameObject& entity, dae::Event event) override;
private:  
   std::shared_ptr<dae::GameObject> m_HealthText;  
};