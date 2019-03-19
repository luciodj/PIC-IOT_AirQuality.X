#include <stdlib.h>
#include <string.h>
#include <math.h> //include libm
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include "adc/adc.h"

#define UART_BAUD_RATE 2400
#include "uart/uart.h"

#include "mq135/mq135.h"

//define mq135 pulldown resistor
#define MQ135_PULLDOWNRES 22000

int main(void) {
	char printbuff[100];
	double d = 0;
	uint16_t adc = 0;

	//init uart
	uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) );

	//init adc
	adc_init();

	//init interrupt
	sei();

	long mq135_ro = 0;

	for (;;) {
		uart_puts("reading...\r\n");

		//get adc
		adc = adc_read(0);

		//calculated resistence depends on the sensor pulldown resistor
		long res = adc_getresistence(adc, MQ135_PULLDOWNRES);
		//get ro
		mq135_ro = mq135_getro(res, MQ135_DEFAULTPPM);
		//convert to ppm (using default ro)
		d = mq135_getppm(res, MQ135_DEFAULTRO);

		itoa(adc, printbuff, 10);
		uart_puts("ADC     "); uart_puts(printbuff); uart_puts("\r\n");

		ltoa(res, printbuff, 10);
		uart_puts("RES     "); uart_puts(printbuff); uart_puts("\r\n");

		ltoa(mq135_ro, printbuff, 10);
		uart_puts("ro      "); uart_puts(printbuff); uart_puts("\r\n");

		dtostrf(d, 3, 5, printbuff);
		uart_puts("ppm     "); uart_puts(printbuff); uart_puts("\r\n");

		uart_puts("\r\n");

		_delay_ms(1000);
	}
	
	return 0;
}
