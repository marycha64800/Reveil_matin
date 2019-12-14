/*
    Name:       reveil_matin.ino
    Created:	05/12/2019 13:07:16
    Author:     Marycha
*/







// The setup() function runs once each time the micro-controller starts
#include <TinyRTClib.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>


LiquidCrystal_I2C lcd(0x27, 20, 4);
//LiquidCrystal_I2C lcd(0x3F,20,4);

void setup()
{
    lcd.init(); // initialisation de l'afficheur
}
void loop()
{
  
}
