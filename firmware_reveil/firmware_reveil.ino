/*
    Name:       reveil_matin.ino
    Created:  05/12/2019 13:07:16
    Author:     Marycha
*/

#include <RTClib.h>
#include <LiquidCrystal_I2C.h>

#define ADRR_LCD 0x3F
#define PIN_SWITCH_ALRM 2
#define PIN_SWICTH_BLUE 3
#define PIN_SWITCH_WHITE 4
#define PIN_SWITCH_BLACK 5
#define PIN_SWITCH_YELLOW 6

// The setup() function runs once each time the micro-controller starts

#include"display_lcd.h"
#include"switch.h"

Screen Lcd(ADRR_LCD, 16, 2);
Switch buttons;
RTC_DS1307 Rtc ;

void setup()
{
    // initiaisation des objets
    Lcd.init();
    Rtc.begin();
    buttons.init(PIN_SWITCH_ALRM, PIN_SWICTH_BLUE, PIN_SWITCH_BLACK, PIN_SWITCH_WHITE, PIN_SWITCH_YELLOW);
  
    Serial.begin(9600);


    // Mise a l'heure du module rtc s'il ne l'etait pas
    if (!Rtc.isrunning())
    {
        Rtc.adjust(DateTime(__DATE__, __TIME__));
    }
}

void loop()
{
  DateTime now = Rtc.now();
  Lcd.display_home(&now);
    
}
