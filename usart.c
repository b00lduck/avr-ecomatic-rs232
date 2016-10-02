#include "stdinc.h"
#include "tools.h"
#include "usart.h"

char buffer[LINEBUFFER_LENGTH];

void usart_init() {

	UBRRH = 0; 
	UBRRL = 95; // 9600 bps

	UCSRB = (1<<RXEN)|(1<<TXEN);
	UCSRC = (1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
}

void USART_TX(char data ) {
	while ( !( UCSRA & (1<<UDRE)) ) {
		wdt_reset();
	}
	UDR = data;	
}

void USART_TXS(char* s) {
	while(*s) {
		USART_TX(*s);
		s++;		
	}	
}

char USART_RX(void) {
    while (!(UCSRA & (1<<RXC))) {
		wdt_reset();
	};
	return UDR;
}

void USART_RXS(void) {
	unsigned char t = 0;
	char* b = buffer;
	unsigned char len = LINEBUFFER_LENGTH;
	do {
 		t = USART_RX();
		if (len) {
			*b++ = t;
			len--;
		}
	} while(t != 13);
	*b = 0; // ende
}
