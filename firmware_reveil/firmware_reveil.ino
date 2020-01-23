/*
    Name:       reveil_matin.ino
    Created:  05/12/2019 13:07:16
    Author:     Marycha
*/

#include <LedControl.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>


#include"setting.h"


void setup()
{
    // initiaisation des objets
    Lcd.init();
    Switch_alarm.init();
    Blue_bttn.init();
    Yelw_bttn.init();
    Wht_bttn.init();
    Blk_bttn.init();
    Eye_left.setup();
    Eye_right.setup();
    

    Rtc.begin();
    Serial.begin(9600);

    
    // Mise a l'heure du module rtc 
   Rtc.adjust(DateTime(__DATE__,__TIME__));
   
    
    delay(500);
}

/*****************************************************************************************************

                                             Main 


******************************************************************************************************/

void loop()
{
  
  DateTime now = Rtc.now();

  //______ affichage ecran principal _____________

  Lcd.display_home(&now, Switch_alarm.ctl_state());

  // __________menu des reglages__________________

  if (Wht_bttn.push()) { set_now(&now); }
  else if (Blk_bttn.push()) { set_alrm(&alarm_setting); }

  // ______________reveil ________________________

  if (Switch_alarm.ctl_state() && alarm_setting.hh == now.hour() && alarm_setting.mm == now.minute() && now.second() == 0) { play_alarm(); }
 
   
}
