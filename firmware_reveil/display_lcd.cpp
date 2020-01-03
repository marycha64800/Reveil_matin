
#include "display_lcd.h"




void Screen::_display_alarm(bool swch_alrm)
{
    if (swch_alrm)
    {
        setCursor(0, 0);
        print("**");
        setCursor(14, 0);
        print("**");

    }
    else
    {
        setCursor(0, 0);
        print("  ");
        setCursor(14, 0);
        print("  ");

    }
    
}
 Screen::_TimeString Screen:: _format_time(int const hh, int const mm, int const ss)
{
    /*
    On formate l'heure s'il elle arrive sous la forme de = 12: 4: 5
    la fonction affiche l'heure sous ce format = 12:04:05
        
    */

    _TimeString buff;
    sprintf(buff.data, "%2d:%02d:%02d", hh, mm, ss);
    return buff;
}




Screen::_DateString Screen::_format_date(int const dayOfTheWeek, int const day, int const month, int const year)
{
    /*
            methoque qui formate la date du jour et renvoie une structure ( tableau ) pour qu'il pouisse etre affiche)
    */
    
    char const* day_format[] = { "Dimanche", "Lundi", "Mardi","Mercredi","Jeudi","Vendredi","Samedi" };
    char const* month_format[] = { "Janvier", "Fervrier", "Mars", "Avril", "Mai", "Juin", "Juillet", "Aout", "Septembre", "Octobre", "Novembre", "Decembre" };
    _DateString date_format;
   
    sprintf(date_format.data, "%s %02d %s %d ", day_format[dayOfTheWeek], day, month_format[month-1], year);// -1 a month pour le permetre d'etre compatible avec les tableaux 
    return date_format;
}




void Screen::_scroll_one_line( char const* text_to_scroll, int const line)
{
    /*
    Methode qui permet de deplacer du texte sur une seule ligne sans bloquer l'excution d'autre programe.

    Pour les besoins des variables globale garde en memoire l'avancer du texte et le delay entre deux affichage 
    La fonction travaille differement a partir du moment ou le texte remplit tout l'ecran. 
    Un pointeur sur le texte et dirige sur le premier caractere tandis que l'on increment un index pour que celui 
    ci demarre l'affichage a partir de ce nouveau index.

    Une fois terminer on remet tout a zero et on peu repartir 
    
    */

    unsigned long current_millis = millis();
    int const size_char = strlen(text_to_scroll);


    if (current_millis - PREVIOUS_MILLIS >= DELAY_SCROLL)// fonction non bloquante le delay et reglable dans le header
    {
        if (INDEX_LCD >= 0 ) // vrai tant que l'ecran n'est pas rempli
        {
            setCursor(INDEX_LCD, line);
            print(text_to_scroll);
            INDEX_LCD--;
            PREVIOUS_MILLIS = current_millis;
        }

        else if (INDEX_LCD <= 0 && INDEX_CHAR <= size_char) //l'ecran est rempli on va maintenant selectioner ce que l'on affiche
        {
           
            if (INDEX_CHAR <= size_char)
            {
                setCursor(INDEX_LCD, line);
                print((text_to_scroll+INDEX_CHAR));// j'increment mon pointeur pour qu'il ne m'affiche que le reste du texte
                INDEX_CHAR++;
                PREVIOUS_MILLIS = current_millis;
            }
            else
            {
                setCursor(0, line);
                print("Err: endScroll");
            }
            
        }
        else if (INDEX_LCD <= 0 && INDEX_CHAR >= size_char) // tout le texte est passer on reinitialise les variable globale
        {
            INDEX_CHAR = 1;
            INDEX_LCD = SIZE_LCD-1;
        }

        else
        {
            setCursor(0, 1);
            print("Err: scroll");
        }
        
    }
    
}




Screen::Screen(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows) : LiquidCrystal_I2C(lcd_Addr, lcd_cols, lcd_rows)
{


}


void Screen::display_home(DateTime* date, bool switch_alrm)
{
    /*
    - on affiche lheure et la date correctement sur l'ecran 16*2 s'il le texte est trop grand (date du jour ) 
    la fonction s'occupe de faire deffiler lecran pour la lecture complete 

    */
    home();
    backlight();
    setCursor(4, 0);
    _TimeString const time = _format_time(date->hour(), date->minute(), date->second());// s'occupe de formater et afficher l'heure
    print(time.data);
    _DateString const today_date = _format_date(date->dayOfTheWeek(), date->day(), date->month(), date->year());

    if (strlen(today_date.data) > 16)
    {       
        _scroll_one_line(today_date.data, 1);
    }
    else
    {
        setCursor(0, 1);
        print(today_date.data);
    }
    _display_alarm(switch_alrm);
}
