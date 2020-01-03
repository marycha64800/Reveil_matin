

#include "switch.h"
#include "arduino.h"

Switch::Switch(int pin )
{
	swicth_pin = pin;
}
	

void Switch::init()
{
	pinMode(swicth_pin, INPUT_PULLUP);
	
}

bool Switch::ctl_state()
{
	if (digitalRead(swicth_pin))
	{
		state = true;
	}
	else
	{
		state = false;
	}
 return state;
}

PushButton::PushButton(int pin) : Switch(pin)
{

}
