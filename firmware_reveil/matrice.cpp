

#include "matrice.h"

Matrice::Matrice(int dataPin, int clkPin, int csPin, int numDevices) : LedControl(dataPin, clkPin, csPin, numDevices)
{

}

void Matrice::setup(uint8_t intens)
{
    clearDisplay(0);
    shutdown(0, false);
    setIntensity(0, 10);
}

uint8_t Matrice::select_img(uint16_t len_img)
{
    if (++i >= len_img) { i = 0;}
    return i;
}

void Matrice::diplay_picture(uint64_t img)
{
    for (int i = 0; i < 8; i++) {
        byte row = (img >> i * 8) & 0xFF;
        for (int j = 0; j < 8; j++) {
            setLed(0, i, j, bitRead(row, j));
        }
    }

}
