#pragma once


#include <LiquidCrystal_I2C.h>
#include <Wire.h>


class Screen {

private:
	LiquidCrystal lcd;
	int adress;

public:
	Screen();
	void init(int aAdress)

};