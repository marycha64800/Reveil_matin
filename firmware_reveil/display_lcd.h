#ifndef SCREEN_H_
#define SCREEN_H_

#include <RTClib.h>
#include <LiquidCrystal_I2C.h>


class Screen : public LiquidCrystal_I2C
{
  private:

      char const _day_format[7][10] = { "Dimanche", "Lundi", "Mardi","Mercredi","Jeudi","Vendredi","Samedi" };
      char const _month_format[12][10] = { "Janvier", "Fervrier", "Mars", "Avril", "Mai", "Juin", "Juillet", "Aout", "Septembre", "Octobre", "Novembre", "Decembre" };

      int8_t _index_char = 1;
      uint32_t _previous_millis;
      uint8_t _size_lcd;
      uint16_t _delay_scroll;
      int8_t _index_lcd;

      template<unsigned N>
      struct _Array
      {
          char data[N];

      };
      using _TimeString = _Array<10>;
      using _DateString = _Array<30>;

      _TimeString _format_time(uint8_t const hh, uint8_t const mm, uint8_t const ss);
      _DateString _format_date(uint8_t const dayOfTheWeek, uint8_t const day, uint8_t const month, uint16_t const year);
      void _scroll_one_line(char const* text_to_s_croll, uint8_t line);
      void _display_alarm(bool swch_alrm);
      
      
  public:

    
    Screen(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows, uint16_t dly_scrll = 500);
    void display_home(DateTime* date, bool switch_alrm);
    void display_set_hour(uint8_t const increm_hh, uint8_t const increm_mm, uint8_t sec);
    void display_set_alrm(uint8_t const hh, uint8_t const mm);
    void display_set_year(uint16_t const yy);
    void display_set_month(uint8_t const mth);
    void display_set_day(uint8_t const dy);
   

    
    //void display_test(char *message);
    
};
#endif
