

#include "setting.h"


/*****************************************************************************************************

                                             Fonction


******************************************************************************************************/




void play_alarm()
{
    Lcd.clear();
    bool pass = true;
    while (Switch_lever.ctl_state())
    {
        Lcd.setCursor(4, 0);
        if (pass) { Lcd.display(); pass = !pass; }
        else { Lcd.noDisplay(); pass = !pass; }
        Lcd.print("DEBOUT !");
        tone(PIN_TONE, 500, 50);

    }
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
