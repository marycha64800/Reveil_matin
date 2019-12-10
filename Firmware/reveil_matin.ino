#include <LiquidCrystal.h>




int const RS{ 11 }, E{ 10 }, D4{ 5 }, D5{ 4 }, D6{ 3 }, D7{ 2 };
LiquidCrystal  screen_lcd(RS, E, D4, D5, D6, D7);


// The setup() function runs once each time the micro-controller starts




void setup()
{
    screen_lcd.begin(16, 2);

}

// Add the main program code into the continuous loop() function
void loop()
{

    screen_lcd.home();
    char display_time[16]{ "" };
    int seconds = (millis() / 1000);
    int minutes = seconds / 60;
    int heures = minutes / 60;
    sprintf(display_time, "%2d:%2d:%2d::%2d", heures, minutes, seconds, millis());
    screen_lcd.setCursor(0, 0);
    screen_lcd.write(display_time);
    screen_lcd.setCursor(0, 1);
    screen_lcd.print(millis() / 1000);

}