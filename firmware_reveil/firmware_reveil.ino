/*
    Name:       reveil_matin.ino
    Created:  05/12/2019 13:07:16
    Author:     Marycha
*/

#include <RTClib.h>
#include <LiquidCrystal_I2C.h>

#include"display_lcd.h"
#include"switch.h"

#define ADRR_LCD 0x3F
#define PIN_SWITCH_ALRM 2
#define PIN_SWICTH_BLUE 3
#define PIN_SWITCH_WHITE 4
#define PIN_SWITCH_BLACK 5
#define PIN_SWITCH_YELLOW 6

// The setup() function runs once each time the micro-controller starts


bool mess = false;
Screen Lcd(ADRR_LCD, 16, 2);
Switch switch_lever(PIN_SWITCH_ALRM);
PushButton blue_bttn(PIN_SWICTH_BLUE), yelw_bttn(PIN_SWITCH_YELLOW), wht_bttn(PIN_SWITCH_WHITE), blk_bttn(PIN_SWITCH_BLACK);
RTC_DS1307 Rtc ;

// prototype

void alarm_shut_down();

void setup()
{
    // initiaisation des objets
    Lcd.init();
    Rtc.begin();
    switch_lever.init();
    blue_bttn.init();
    yelw_bttn.init();
    wht_bttn.init();
    blk_bttn.init();
    Serial.begin(9600);


    // Mise a l'heure du module rtc 
   Rtc.adjust(DateTime(__DATE__, __TIME__));
    // interruption de l'alarme 
    attachInterrupt(0,alarm_shut_down,FALLING);
}

void loop()
{
  DateTime now = Rtc.now();
  Lcd.display_home(&now,switch_lever.ctl_state());
  
  
}

void alarm_shut_down()
{
    switch_lever.state = false;
}
