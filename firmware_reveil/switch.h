#ifndef SWITCH_H_
#define SWITCH_H_



/*
	module implemente les fonctions de chaque bouton 

*/
#include "arduino.h"


class Switch
{
public:
	Switch(uint8_t pin);
	void init();
	bool ctl_state();
	uint8_t  swicth_pin;

protected:
	int _delay_push = 70;

};



class PushButton : public Switch
{
public:
	PushButton(uint8_t pin );
	struct Command
	{
		bool action = false;
		uint8_t increment = 0;
		
	};
	Command long_push();
	bool push();

private:
	

};


#endif
