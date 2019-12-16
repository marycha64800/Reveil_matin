


#include "display_lcd.h"



Screen::Screen(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows) : LiquidCrystal_I2C(lcd_Addr, lcd_cols, lcd_rows)
{


}

void Screen::Setup(bool aState_alarm)
{

    state_alarm = aState_alarm;

}

void Screen::display_now(DateTime* date)
{
    home();
    backlight();
    setCursor(4, 0);
    char format_time[16] = "";
    sprintf(format_time, "%2d:%2d:%2d" , date->hour(),date->minute(),date->second());
    print(format_time);
    

}

/*void Screen::display_test(char* message)
{
    home();
    backlight();
    setCursor(0, 0);
    print(message);
    print(", je mesure: ");
    print(strlen(message));
    print("C");
}
*/
