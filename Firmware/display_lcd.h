#ifndef SCREEN_H_
#define SCREEN_H_

#include <LiquidCrystal_I2C.h>
#include <RTClib.h>


class Screen : public LiquidCrystal_I2C
{
  private:
 

  public:
    Screen(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows);
    void Setup(bool aState_alarm);
    void display_now(DateTime* date);
    void display_test(char *message);
    bool state_alarm;
};
#endif
