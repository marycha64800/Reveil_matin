
#include "display_lcd.h"



char* Screen::_format_time(int hh, int mm, int ss)
{
    /*
    On formate l'heure s'il elle arrive sous la forme de = 12: 4: 5
    la fonction retourne l'heure sous ce format = 12:04:05

    data contient les donnee "temps" brute formated_data sera le tableau retourner par la fonction 
    sa taille doit etre allouee dynamiquement pour etre retournee " fonction calloc(taille tableau,sizeof(char))
    deplus du fait de le compilateur compile en c++ il ne tolere pas la conversion void* en char que retroune calloc 
    la solution est de caster "forcer" le retour en pointeur sur char 
    attention il faudras librere la memoire ensuite 
    
    */
    char buff[3] = "";
    int i;
    int data[3] = {hh, mm, ss};
    char* formated_data = NULL;
    formated_data = (char*)calloc(16 ,sizeof(char)); 
   
    for (i = 0; i < 3; i++)
    {
        sprintf(buff, "%d", data[i]);

        if (strlen(buff) < 2 && data[i] != hh) // on ne veut pas que les heures soit avec un zero au debut 
        {
            char c[2] = "0"; // on cree notre 0 artificiel
            strcat(c, buff);// on colle notre heure derriere
            strcpy(buff, c);// on remet le tout dans buff pour conserver le meme nom de variable 

        }
        if (i < 2)
            {
                strcat(buff, ":"); // ajout des deux point entre chaque champs mais on evite de le mettre a la fin
            }
        strcat(formated_data, buff);
    }
    return formated_data;
}

char* Screen::_format_date(int const dayOfTheWeek, int const day, int const month, int const year)
{
    /*
    on va formater la date pour quelle affiche le jour en toutes lettre
    
    */


    return nullptr;
}

Screen::Screen(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows) : LiquidCrystal_I2C(lcd_Addr, lcd_cols, lcd_rows)
{


}

void Screen::Setup(bool aState_alarm)
{

    state_alarm = aState_alarm;

}

void Screen::display_home(DateTime* date)
{
    /*
    - on affiche lheure et la date correctement sur l'ecran 16*2 s'il le texte est trop grand (date du jour ) 
    la fonction s'occupe de faire deffiler lecran pour la lecture complete 

    */
    home();
    backlight();
    setCursor(4, 0);
    char* time = _format_time( date->hour(), date->minute(), date->second());
    print(time);
    free(time);
    char* date = _format_date(date->dayOfTheWeek(), date->day(), date->month(), date->year());
 

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
