#ifndef MATRICE_H_
#define MATRICE_H_

#include <avr/pgmspace.h>
#include <LedControl.h>

const uint64_t SPACE_INVADER[2] PROGMEM = { 
            0x24a5a5ffdb7e2424,
            0x81427c7edbffa5a5 
        };
   
    const uint64_t ARROW[17] PROGMEM = {
          0x0000000000000000,
          0x1800000000000000,
          0x2418000000000000,
          0x5a24180000000000,
          0xa55a241800000000,
          0x5aa55a2418000000,
          0xa55aa55a24180000,
          0x42a55aa55a241800,
          0x8142a55aa55a2418,
          0x008142a55aa55a24,
          0x00008142a55aa55a,
          0x0000008142a55aa5,
          0x0000008142249942,
          0x0000000081422499,
          0x0000000000814224,
          0x0000000000008142,
          0x0000000000000081
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
