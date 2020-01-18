
#include "display_lcd.h"


Screen::Screen(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows) : LiquidCrystal_I2C(lcd_Addr, lcd_cols, lcd_rows)
{
    _size_lcd = lcd_cols;
    _index_lcd = _size_lcd - 1;
    _previous_millis = 0;
}

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
Screen::_TimeString Screen::_format_time(uint8_t const hh, uint8_t const mm, uint8_t const ss)
{
    /*
    On formate l'heure s'il elle arrive sous la forme de = 12: 4: 5
    la fonction affiche l'heure sous ce format = 12:04:05
        
    */

    _TimeString buff;
    sprintf(buff.data, "%2d:%02d:%02d", hh, mm, ss);
    return buff;
}


Screen::_DateString Screen::_format_date(uint8_t const dayOfTheWeek, uint8_t const day, uint8_t const month, uint16_t const year)
{
    /*
            methoque qui formate la date du jour et renvoie une structure ( tableau ) pour qu'il pouisse etre affiche)
    */
    _DateString date_format;
    sprintf(date_format.data, "%s %02d %s %d ", _day_format[dayOfTheWeek], day, _month_format[month-1], year);// -1 a month pour le permetre d'etre compatible avec les tableaux 
    return date_format;
}




void Screen::_scroll_one_line( char const* text_to_scroll, uint8_t const line, uint16_t delay_scroll = 500)
{
    /*
    Methode qui permet de deplacer du texte sur une seule ligne sans bloquer l'excution d'autre programme.

    Pour les besoins des variables globale garde en memoire l'avancee du texte et le delay entre deux affichage 
    La fonction travaille differement a partir du moment ou le texte remplit tout l'ecran. 
    Un pointeur sur le texte et dirige sur le premier caractere tandis que l'on increment un index pour que celui 
    ci demarre l'affichage a partir de ce nouveau index.

    Une fois terminer on remet tout a zero et on peu repartir 
    
    */

    uint8_t const size_char = strlen(text_to_scroll);


    if (millis() - _previous_millis >= delay_scroll)// fonction non bloquante le delay et reglable dans le header
    {
        if (_index_lcd >= 0 ) // vrai tant que l'ecran n'est pas rempli
        {
            setCursor(_index_lcd, line);
            print(text_to_scroll);
            _index_lcd--;
            _previous_millis = millis();
        }

        else if (_index_lcd <= 0 && _index_char <= size_char) //l'ecran est rempli on va maintenant selectioner ce que l'on affiche
        {
           
            if (_index_char <= size_char)
            {
                setCursor(_index_lcd, line);
                print((text_to_scroll+_index_char));// j'increment mon pointeur pour qu'il ne m'affiche que le reste du texte
                _index_char++;
                _previous_millis = millis();
            }

        }

        else if (_index_lcd <= 0 && _index_char >= size_char) // tout le texte est passe on reinitialise les variables 
        {
            _index_char = 1;
            _index_lcd = _size_lcd - 1;
        }

    }
    
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

    if (strlen(today_date.data) > _size_lcd)
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



void Screen::display_set_hour(uint8_t const increm_hh, uint8_t const increm_mm, uint8_t const sec)
{
    /*
        fonction qui va formater l'affichage du menu 'reglage de l'heure' 
    */

    setCursor(1, 0);
    print("REGLAGE HEURE:");
    setCursor(4, 1);
    _TimeString time;
    sprintf(time.data,"%02d:%02d:%02d", increm_hh, increm_mm, sec);
    print(time.data);
}

void Screen::display_set_alrm(uint8_t hh, uint8_t mm)
{
    setCursor(0, 0);
    print("*REGLAGE ALARME*");
    setCursor(5, 1);
    char buff[6];
    sprintf(buff, "%02d:%02d", hh, mm);
    print(buff);
}

void Screen::display_set_year(uint16_t const yy)
{
    setCursor(1, 0);
    print("REGLAGE ANNEE:");
    setCursor(6, 1);
    print(yy);
}

void Screen::display_set_month(uint8_t const mth)
{
    setCursor(0, 0);
    print("REGLAGE MOIS:");
    setCursor(13, 0);
    char buff[10];
    sprintf(buff, "%02d", mth);
    print(buff);
    setCursor(0, 1);
    sprintf(buff, "%10s", _month_format[mth-1]);
    print(buff);
    
}

void Screen::display_set_day(uint8_t const dy)
{
    setCursor(1, 0);
    print("REGLAGE JOUR:");
    setCursor(6, 1);
    char buff[3];
    sprintf(buff, "%02d", dy);
    print(buff);
}

void Screen::display_alarm(bool* first_pass)
{
    if (*first_pass) { clear(); }
    *first_pass = false;
    setCursor(4, 0);
    if (*first_pass % 2) { display(); }
    else { noDisplay(); }
    print("Debout!");
}
