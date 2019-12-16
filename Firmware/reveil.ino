

/*
    Name:       reveil_matin.ino
    Created:  05/12/2019 13:07:16
    Author:     Marycha
*/



// The setup() function runs once each time the micro-controller starts

#include <LiquidCrystal_I2C.h>
#include <RTClib.h>

#include"display_lcd.h"

Screen Lcd(0x27, 20, 4);
RTC_DS1307 Rtc ;

void setup()
{
    // initiaisation des objets
    Lcd.init();
    Wire.begin();
    Rtc.begin();

    // Mise a l'heure du module rtc s'il ne l'etait pas
    if (!Rtc.isrunning())
    {
        Rtc.adjust(DateTime(__DATE__, __TIME__));
    }

}

void loop()
{
  DateTime now = Rtc.now();  
    Lcd.display_now(&now);
}
