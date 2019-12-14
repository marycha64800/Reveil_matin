#include "ecran.h"


void Screen::display()
{
	home();
	setCursor(4, 0);
	char format_time[16] = "";
	sprintf(format_time, "%2s:%2s:%2s", _hour, _min, _sec);
	print(format_time);
}

Screen::Screen(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows) : LiquidCrystal_I2C(lcd_Addr, lcd_cols, lcd_rows)
{	
	
	
}

void Screen::Setup(byte aDate, byte aMonth, byte aYear, byte aHours, byte aMin, byte aSec, byte aState_alarm, byte aPin_white_button, byte aPin_alarm)
{
	_day = aDate;
	_month = aMonth;
	_year = aYear;
	_pin_alarm = aPin_alarm ;
	_white_button = aPin_white_button;

}
