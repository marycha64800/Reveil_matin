

#include "switch.h"
#include "arduino.h"

Switch::Switch(int pin )
{
	swicth_pin = pin;
}
	

void Switch::init()
{
	pinMode(swicth_pin, INPUT);
	
}

bool Switch::ctl_state()
{
  delay(_delay_push);
	if (digitalRead(swicth_pin))
	{
		state = false;
	}
	else
	{
		state = true;
	}
 return state;
}

PushButton::PushButton(int pin) : Switch(pin)
{

}



PushButton::Command PushButton::long_push()
{
	Command order;
	if (ctl_state())
	{
		order.action = true;
		order.increment = 1;
	}
	else
	{
		order.action = false;
		order.increment = 0;
	}
	return order;
}
