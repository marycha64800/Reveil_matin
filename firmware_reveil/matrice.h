#ifndef MATRICE_H_
#define MATRICE_H_

#include <avr/pgmspace.h>
#include <LedControl.h>


class Matrice : public LedControl
{

	public:
		Matrice(int dataPin, int clkPin, int csPin, int numDevices = 1);

		template <unsigned N>
		struct Picture
		{
			const uint64_t data[N];
			const uint16_t size = sizeof(data) / 8;

		};

		using space_invader = Picture<2>;
		



	private:





		
};

	





#endif // !MATRICE_H_
