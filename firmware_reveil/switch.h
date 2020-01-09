#ifndef SWITCH_H_
#define SWITCH_H_



/*
	module implemente les fonctions de chaque bouton 

*/



class Switch
{
public:
	Switch(int pin);
	void init();
	volatile bool state;
	bool ctl_state();
	

protected:
	 int  swicth_pin;

private:
  int _delay_push = 70;

};



class PushButton : public Switch
{
public:
	PushButton(int pin);
	struct Command
	{
		bool action = false;
		int increment = 0;
		unsigned long prev = 0;
	};
	Command long_push();

protected:

	

private:
	

};


#endif
