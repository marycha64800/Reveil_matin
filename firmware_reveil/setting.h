#ifndef SETTING_H_
#define SETTING_H_

#include <RTClib.h>
#include <LiquidCrystal_I2C.h>

#include"display_lcd.h"
#include"switch.h"

const uint8_t ADRR_LCD = 0x3F;
const uint8_t PIN_SWITCH_ALRM = 2;
const uint8_t PIN_SWICTH_BLUE = 3;
const uint8_t PIN_SWITCH_WHITE = 4;
const uint8_t PIN_SWITCH_BLACK = 5;
const uint8_t PIN_SWITCH_YELLOW = 6;
const uint8_t PIN_TONE = 7;

struct NewSettingValue
{
    uint8_t hh = 0;
    uint8_t mm = 0;
    uint8_t ss = 0;
    uint16_t yy = 0;
    uint8_t mth = 0;
    uint8_t dy = 0;
    uint8_t dy_of_wk = 0;
};


/*****************************************************************************************************

                                         Prototype


******************************************************************************************************/


void play_alarm();
void set_now(DateTime* date);
void set_hours(uint8_t hh, uint8_t mm, uint8_t ss, NewSettingValue* new_value);
void set_alrm(NewSettingValue* alarm);
uint8_t set_day(uint8_t dy);
uint8_t set_month(uint8_t mth);
uint16_t set_year(uint16_t yy);


/*****************************************************************************************************

                                       Creation des objets


******************************************************************************************************/

Screen Lcd(ADRR_LCD, 16, 2);
Switch Switch_lever(PIN_SWITCH_ALRM);
PushButton Blue_bttn(PIN_SWICTH_BLUE), Yelw_bttn(PIN_SWITCH_YELLOW), Wht_bttn(PIN_SWITCH_WHITE), Blk_bttn(PIN_SWITCH_BLACK);
RTC_DS1307 Rtc;
NewSettingValue alarm_setting;



#endif // !SETTING_H_

