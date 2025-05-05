#pragma once  
#include "Observer.h"  
class HealthObserver :  
	public dae::Component, 
	public dae::Observer  
{  
public:  
   HealthObserver();  
   virtual ~HealthObserver() = default;  

   virtual void onNotify(dae::GameObject& entity, dae::Event event) override;
};