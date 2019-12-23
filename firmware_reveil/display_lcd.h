#ifndef SCREEN_H_
#define SCREEN_H_
#define DELAY_SCROLL 500
#define SIZE_LCD 16

#include <LiquidCrystal_I2C.h>
#include <RTClib.h>

static int INDEX_CHAR = 1;
static int INDEX_LCD = SIZE_LCD - 1;
static unsigned long PREVIOUS_MILLIS = 0;


class Screen : public LiquidCrystal_I2C
{
  private:
      void _format_time(int const hh, int const mm, int const ss);
      char* _format_date(int const dayOfTheWeek, int const day, int const month, int const year);
      void _scroll_one_line(char* text_to_scroll, int line);
    
  public:
    Screen(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows);
    void Setup(bool aState_alarm);
    void display_home(DateTime* date);
    
    //void display_test(char *message);
    volatile bool state_alarm;
};
#endif
