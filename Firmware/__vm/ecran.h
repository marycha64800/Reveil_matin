#pragma once


#include <LiquidCrystal_I2C.h>
#include <Wire.h>


class Screen : public LiquidCrystal_I2C {

private:
	byte _day;
	byte _month;
	byte _hour;
	byte _min;
	byte _sec;
	byte _year;
	byte _pin_alarm;
	byte _white_button;
	void display();

public:
	Screen(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows);
	void Setup(byte aDate, byte aMonth, byte aYear,byte aHours,byte aMin, byte aSec , byte aState_alarm, byte aPin_white_button, byte aPin_alarm);

};