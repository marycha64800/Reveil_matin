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


};



class PushButton : public Switch
{
public:
	PushButton(int pin);


protected:


};


#endif
