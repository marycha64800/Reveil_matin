
#include "display_lcd.h"



void Screen::_format_time(int hh, int mm, int ss)
{
    /*
    On formate l'heure s'il elle arrive sous la forme de = 12: 4: 5
    la fonction affiche l'heure sous ce format = 12:04:05

    */

    char buff[10];
    sprintf(buff, "%2d:%02d:%02d", hh, mm, ss);
    print(buff);
}

char* Screen::_format_date(int const dayOfTheWeek, int const day, int const month, int const year)
{
    /*
    on va formater la date pour quelle affiche le jour et le mois en toutes lettres
    
    */
    char* format_data = (char*)calloc(50, sizeof(char));
    char buff[12]="";
    int data[] = { dayOfTheWeek, day, month, year }; // attention l'ordre du tableau est important 
    
    for (int i = 0; i < 4; i++)
    {
        if (i == 0) 
        {
            switch (data[i])
            {
            case 1: strcpy(buff, "Lundi"); break;
            case 2: strcpy(buff, "Mardi"); break;
            case 3: strcpy(buff, "Mercredi"); break;
            case 4: strcpy(buff, "Jeudi"); break;
            case 5: strcpy(buff, "Vendredi"); break;
            case 6: strcpy(buff, "Samedi"); break;
            case 0: strcpy(buff, "Dimanche"); break;
            default: strcpy(buff, "Err: Jour"); break;
            }

        }
        else if (i == 2)
        {
            switch (data[i])
            {
            case 1: strcpy(buff, "Janvier"); break;
            case 2: strcpy(buff, "Fevrier"); break;
            case 3: strcpy(buff, "Mars"); break;
            case 4: strcpy(buff, "Avril"); break;
            case 5: strcpy(buff, "Mai"); break;
            case 6: strcpy(buff, "Juin"); break;
            case 7: strcpy(buff, "Juillet"); break;
            case 8: strcpy(buff, "Aout"); break;
            case 9: strcpy(buff, "Septembre"); break;
            case 10: strcpy(buff, "Octobre"); break;
            case 11: strcpy(buff, "Novembre"); break;
            case 12: strcpy(buff, "Decembre"); break;
            default: strcpy(buff, "Err: Mois"); break;
            }
        }
        else
        {
            sprintf(buff, " %d ", data[i]);
        }
        
        strcat(format_data, buff);


    }

    return format_data;
}

void Screen::_scroll_one_line(char* text_to_scroll, int line)
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
    int size_char = strlen(text_to_scroll);


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
                char* scroll_end = text_to_scroll; // je posisione le pointeur sur le debut de mon texte
                setCursor(INDEX_LCD, line);
                print((scroll_end+INDEX_CHAR));// j'increment mon pointeur pour qu'il ne m'affiche que le reste du texte
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
    _format_time(date->hour(), date->minute(), date->second());// s'occupe de formater et afficher l'heure
    
    char* today_date = _format_date(date->dayOfTheWeek(), date->day(), date->month(), date->year());
    if (strlen(today_date) > 16)
    {       
        _scroll_one_line(today_date, 1);
        free(today_date);
    }
    else
    {
        setCursor(0, 1);
        print(today_date);
    }
    
    

 

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
