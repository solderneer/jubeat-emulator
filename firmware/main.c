#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	for (;;) {
		_delay_ms(500);
        DDRB = 0x00;

	}
	return -1;
}