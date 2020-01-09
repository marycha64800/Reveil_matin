#ifndef SCREEN_H_
#define SCREEN_H_

#include <RTClib.h>
#include <LiquidCrystal_I2C.h>

constexpr auto DELAY_SCROLL = 500;
constexpr auto SIZE_LCD = 16;


static int INDEX_CHAR = 1;
static int INDEX_LCD = SIZE_LCD - 1;
static unsigned long PREVIOUS_MILLIS = 0;




class Screen : public LiquidCrystal_I2C
{
  private:

      char const _day_format[7][10] = { "Dimanche", "Lundi", "Mardi","Mercredi","Jeudi","Vendredi","Samedi" };
      char const _month_format[12][10] = { "Janvier", "Fervrier", "Mars", "Avril", "Mai", "Juin", "Juillet", "Aout", "Septembre", "Octobre", "Novembre", "Decembre" };


      template<unsigned N>
      struct _Array
      {
          char data[N];

      };
      using _TimeString = _Array<20>;
      using _DateString = _Array<50>;

      _TimeString _format_time(int const hh, int const mm, int const ss);
      _DateString _format_date(int const dayOfTheWeek, int const day, int const month, int const year);
      void _scroll_one_line(char const* text_to_scroll, int line);
      void _display_alarm(bool swch_alrm);
      
      
  public:

    Screen(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows);
    void display_home(DateTime* date, bool switch_alrm);
    void display_set_hour(int const increm_hh, int const increm_mm, int sec);
    void display_set_alrm(int const hh, int const mm);
    void display_set_year(unsigned long const yy);
    void display_set_month(int const mth);
    void display_set_day(int const dy);
   

    
    //void display_test(char *message);
    
};
#endif
