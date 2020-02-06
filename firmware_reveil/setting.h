#ifndef SETTING_H_
#define SETTING_H_



#include"display_lcd.h"
#include"switch.h"
#include "matrice.h"

const uint8_t ADRR_LCD = 0x3F;
const uint8_t PIN_SWITCH_ALRM = 2;
const uint8_t PIN_SWICTH_BLUE = 3;
const uint8_t PIN_SWITCH_WHITE = 4;
const uint8_t PIN_SWITCH_BLACK = 5;
const uint8_t PIN_SWITCH_YELLOW = 6;
const uint8_t PIN_TONE = 7;
const uint8_t PIN_CLK_1 = 8;
const uint8_t PIN_CS_1 = 9;
const uint8_t PIN_DIN_1 = 10;
const uint8_t PIN_CLK_2 = 11;
const uint8_t PIN_CS_2 = 12;
const uint8_t PIN_DIN_2 = 13;


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
Switch Switch_alarm(PIN_SWITCH_ALRM);
PushButton Blue_bttn(PIN_SWICTH_BLUE), Yelw_bttn(PIN_SWITCH_YELLOW), Wht_bttn(PIN_SWITCH_WHITE), Blk_bttn(PIN_SWITCH_BLACK);
RTC_DS1307 Rtc;
NewSettingValue alarm_setting;
Matrice Eye_left(PIN_DIN_1, PIN_CLK_1, PIN_CS_1), Eye_right(PIN_DIN_2, PIN_CLK_2, PIN_CS_2);



/*****************************************************************************************************

                                             Fonction


******************************************************************************************************/
void play_anim(uint64_t sp_1, uint64_t sp_2)
{
  
    memcpy_P(&sp_1, &SPACE_INVADER[Eye_left.select_img(LEN_SPACE_INVADER)], 8 );
    memcpy_P(&sp_2, &ARROW[Eye_right.select_img(LEN_ARROW)], 8);
    Eye_left.diplay_picture(sp_1);
    Eye_right.diplay_picture(sp_2);
    
}
    



void play_alarm()
{
    Lcd.clear();
    uint64_t sprite_1;
    uint64_t sprite_2;
    uint64_t previous_millis = millis();
    while (Switch_alarm.ctl_state())
    {
        Lcd.setCursor(4, 0);
        Lcd.print("DEBOUT !");

        if(millis() - previous_millis >= 100)
        { 
          play_anim(sprite_1, sprite_2);
          previous_millis = millis(); 
        }
        else if (millis() - previous_millis >= 50) { tone(PIN_TONE, 500, 25); }
      
       

    }
    
    Eye_left.setup();
    Eye_right.setup();
}

void set_now(DateTime* date)
{
    NewSettingValue new_val;
    new_val.yy = set_year(date->year());
    new_val.mth = set_month(date->month());
    new_val.dy = set_day(date->day());
    set_hours(date->hour(), date->minute(), date->second(), &new_val);
    Serial.println(new_val.hh);

    Rtc.adjust(DateTime(new_val.yy, new_val.mth, new_val.dy, new_val.hh, new_val.mm, new_val.ss));

}

uint8_t set_day(uint8_t dy)
{

    Lcd.clear();
    while (!Wht_bttn.push())
    {
        if (Blue_bttn.long_push().action)
        {
            dy = dy + Blue_bttn.long_push().increment;
            if (dy >= 32) { dy = 1; }
        }
        else if (Yelw_bttn.long_push().action)
        {
            dy = dy - Yelw_bttn.long_push().increment;
            if (dy <= 0) { dy = 31; }
        }
        Lcd.display_set_day(dy);
    }
    Lcd.clear();
    return dy;
}



uint8_t set_month(uint8_t mth)
{

    Lcd.clear();
    while (!Wht_bttn.push())
    {
        if (Blue_bttn.long_push().action)
        {
            mth = mth + Blue_bttn.long_push().increment;
            if (mth >= 13) { mth = 1; }
        }
        else if (Yelw_bttn.long_push().action)
        {
            mth = mth - Yelw_bttn.long_push().increment;
            if (mth <= 0) { mth = 12; }
        }
        Lcd.display_set_month(mth);
    }
    Lcd.clear();
    return mth;
}

uint16_t set_year(uint16_t yy)
{

    Lcd.clear();
    while (!Wht_bttn.push())
    {
        if (Blue_bttn.long_push().action)
        {
            yy = yy + Blue_bttn.long_push().increment;
        }
        else if (Yelw_bttn.long_push().action)
        {
            yy = yy - Yelw_bttn.long_push().increment;
            if (yy < 2020) { yy = 2020; }
        }
        Lcd.display_set_year(yy);
    }
    Lcd.clear();
    return yy;
}

void set_hours(uint8_t hh, uint8_t mm, uint8_t ss, NewSettingValue* new_value)
{
    new_value->hh = hh;
    new_value->mm = mm;
    new_value->ss = ss;
    Lcd.clear();
    while (!Wht_bttn.push())
    {
        if (Blue_bttn.long_push().action)
        {
            new_value->hh = new_value->hh + Blue_bttn.long_push().increment;
            if (new_value->hh >= 24) { new_value->hh = 0; }
        }
        else if (Yelw_bttn.long_push().action)
        {
            new_value->mm = new_value->mm + Yelw_bttn.long_push().increment;
            if (new_value->mm >= 60) { new_value->mm = 0; }
        }
        else if (Blk_bttn.long_push().action) { new_value->ss = 0; }
        Lcd.display_set_hour(new_value->hh, new_value->mm, new_value->ss);
    }
    Lcd.clear();
}

void set_alrm(NewSettingValue* alarm)
{


    Lcd.clear();
    while (!Blk_bttn.push())
    {

        if (Blue_bttn.long_push().action)
        {
            alarm->hh = alarm->hh + Blue_bttn.long_push().increment;
            if (alarm->hh >= 24) { alarm->hh = 0; }
        }
        else if (Yelw_bttn.long_push().increment)
        {
            alarm->mm = alarm->mm + Yelw_bttn.long_push().increment;
            if (alarm->mm >= 60) { alarm->mm = 0; }
        }
        Lcd.display_set_alrm(alarm->hh, alarm->mm);
    }
    Lcd.clear();
}



#endif // !SETTING_H_
