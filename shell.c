#include "stdinc.h"
#include "usart.h"
#include "adc.h"
#include "crc8.h"
#include "cmdparser.h"

char buffer2[64];
unsigned char rc;

void doDumpCommand() {
	
	// Datagram:
	// aaa bbb ccc ddd eee fff ggg hhh ii jj\n
	//
	// Datagram length is 8*4 + 2*3 = 32 + 6 = 38
	// 
	// all values in hex
	// aaa...hhh 10-Bit ADC value of ADC0(a) to ADC7(h)
	// ii Digital inputs C0-C7
	// jj CRC8 checksum of the distinct values (without spaces)
	
	crc_init();
	
	for (uint8_t i=0; i < 8; i++) {
		uint16_t aval = ADC_Read_Avg(i, 16);
		crc16(aval);
		sprintf(buffer2,"%03x ", aval);
		USART_TXS(buffer2);
	}
	uint8_t dval = ~PINC;
	uint8_t crc = crc8(dval);
	sprintf(buffer2,"%02x ", dval);
	USART_TXS(buffer2);

	sprintf(buffer2,"%02x\n", crc);
	USART_TXS(buffer2);
		
}


void doInfoCommand() {

	uint16_t aval = ADC_Read_Avg(7, 16);
	float fval = (float)aval * (4.97f / 1024.0f);
	sprintf(buffer2,"Kesseltemperatur: %04x (%01.3f V)\n", aval, fval);
	USART_TXS(buffer2);

	aval = ADC_Read_Avg(6, 16);
	fval = (float)aval * (4.97f / 1024.0f);
	sprintf(buffer2,"Aussentemperatur: %04x (%01.3f V)\n", aval, fval);
	USART_TXS(buffer2);

	aval = ADC_Read_Avg(5, 16);
	fval = (float)aval * (4.97f / 1024.0f);
	sprintf(buffer2,"Brauchwassertemperatur: %04x (%01.3f V)\n", aval, fval);
	USART_TXS(buffer2);
	
	uint8_t dval = ~PINC;

	USART_TXS("Zikrulationspumpe: ");
	if (dval & (1 << 0)) {
		USART_TXS("EIN\n");		
	} else {
		USART_TXS("AUS\n");		
	}
	
	USART_TXS("Ladepumpe: ");
	if (dval & (1 << 1)) {
		USART_TXS("EIN\n");
		} else {
		USART_TXS("AUS\n");
	}

	USART_TXS("Sommer/Winter: ");
	if (dval & (1 << 2)) {
		USART_TXS("WINTER\n");
		} else {
		USART_TXS("SOMMER\n");
	}

	USART_TXS("Umwaelzpumpe: ");
	if (dval & (1 << 3)) {
		USART_TXS("EIN\n");
		} else {
		USART_TXS("AUS\n");
	}

	USART_TXS("Brenner: ");
	if (dval & (1 << 4)) {
		USART_TXS("EIN\n");
		} else {
		USART_TXS("AUS\n");
	}

	USART_TXS("Nachtabsenkung: ");
	if (dval & (1 << 5)) {
		USART_TXS("TAG\n");
		} else {
		USART_TXS("NACHT\n");
	}
	
}

void shell() {	
	
	while(1) {
	
		USART_RXS();
		
		char cmd[MAXCMDLEN];
		memset(cmd,0,MAXCMDLEN);

		parseCommand(buffer,cmd);

		if (strncmp(cmd,"DUMP",4) == 0) {			
			doDumpCommand();		
		} else if (strncmp(cmd,"INFO",4) == 0) {
			doInfoCommand();			
		} else if (strncmp(cmd,"NOP",3) == 0) {			
			USART_TXS("NOP\n");
		} else if (strncmp(cmd,"HELP",4) == 0) {
			USART_TXS("Available commands are:\nDUMP\nNOP\nHELP\n");			
		} else {			
			USART_TXS("ERROR\n");			
		}

	}

}
