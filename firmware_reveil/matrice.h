#ifndef MATRICE_H_
#define MATRICE_H_

#include <avr/pgmspace.h>
#include <LedControl.h>

const uint64_t SPACE_INVADER[2] PROGMEM = { 
            0x1e3cef3c3cef3c1e,
            0xf13eec3c3cec3ef1
        };
   
    const uint64_t ARROW[17] PROGMEM = {
          0x0000000000000000,
          0x3c18000000000000,
          0x7e3c180000000000,
          0xe77e3c1800000000,
          0x81c3e77e3c180000,
          0x0081c3e77e3c1800,
          0x000081c3e77e3c18,
          0x00000081c3e77e3c,
          0x0000000081c3e77e
        };

    const uint16_t LEN_SPACE_INVADER = sizeof(SPACE_INVADER) / 8;
    const uint16_t LEN_ARROW = sizeof(ARROW) / 8;

class Matrice : public LedControl
{

	public:
		Matrice(int dataPin, int clkPin, int csPin, int numDevices = 1);
    void setup(uint8_t intens=10);
        uint8_t select_img(uint16_t len_img);
        void diplay_picture(uint64_t img);

		

	private:

        uint64_t _previous_millis = 0;
        uint8_t i;
       


				
};

#endif // !MATRICE_H_
