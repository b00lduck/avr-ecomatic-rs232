#include "stdinc.h"

#include "usart.h"
#include "shell.h"
#include "adc.h"
#include "tools.h"

int main(void) {

	// Digital inputs with pullups
	DDRC = 0x00;
	PORTC = 0xff;

	wdt_enable(WDTO_2S);

	usart_init();
	
	ADC_Init();

	//USART_TXS("MCU ready.\n");

	sei();

	shell();

	while(1) { }

}



