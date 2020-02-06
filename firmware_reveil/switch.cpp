

#include "switch.h"



Switch::Switch(uint8_t pin )
{
	swicth_pin = pin;
}
	

void Switch::init()
{
	pinMode(swicth_pin, INPUT);
	
}

bool Switch::ctl_state()
{
	/*
		retourne l'etat du bouton "NF"
	*/
 return digitalRead(swicth_pin);
}

PushButton::PushButton(uint8_t pin) : Switch(pin)
{


}



PushButton::Command PushButton::long_push()
{
	Command order;
	if (ctl_state())
	{
		order.action = true;
		order.increment = 1;
    delay(_delay_push);
	}
	else
	{
		order.action = false;
		order.increment = 0;
    delay(_delay_push);
	}
	return order;
}

bool PushButton::push()
{
	/*
		fonction qui arrete le programe tant que l'on a pas relacher le bouton 
		on peu ajouter des fonctionalitees au bonton 
	
	*/
	if (ctl_state())
	{
		do
		{
			/*
				fonctionalites possible "son , message relacher etc..."
			*/
		} while (ctl_state() != false);
		return true;

	}
	else { return false; }
	
}
