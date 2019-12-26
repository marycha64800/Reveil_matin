/*
    Name:       reveil_matin.ino
    Created:  05/12/2019 13:07:16
    Author:     Marycha
*/
#define ADRR_LCD 0x3F
#define PIN_SWITCH_ALRM 2

// The setup() function runs once each time the micro-controller starts

#include"display_lcd.h"

Screen Lcd(ADRR_LCD, 16, 2);
RTC_DS1307 Rtc ;

void setup()
{
    // initiaisation des objets
    Lcd.init();
    Rtc.begin();
    Serial.begin(9600);

    // Mise a l'heure du module rtc s'il ne l'etait pas
    if (!Rtc.isrunning())
    {
        Rtc.adjust(DateTime(__DATE__, __TIME__));
    }
   // declaration des pins

    pinMode(PIN_SWITCH_ALRM, INPUT);
}

void loop()
{
  DateTime now = Rtc.now();
  Lcd.Setup(digitalRead(PIN_SWITCH_ALRM));
  Lcd.display_home(&now);
    
}
