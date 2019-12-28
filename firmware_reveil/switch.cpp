

#include "switch.h"

Switch::Switch()
{

}

void Switch::init(int swch_1, int swch_2, int swch_3, int swch_4, int swch_5)
{
	int init_pin[5]{ swch_1,swch_2,swch_3,swch_4,swch_5 };
	for (int i{ 0 }; i < 5; i++)
	{
		pinMode(init_pin[i], INPUT_PULLUP);
	}
}
