#include "stdinc.h"

uint8_t reg = 0;

void crc_init() {
	reg = 0;
}

uint8_t crc8(uint8_t byte) {
	
	uint8_t i;
	uint8_t flag;
	uint8_t poly = 0xd5;

	for(uint8_t i=0; i < 8; i++) {
		if (reg & 0x80) {
			flag = 1;
		} else { 
			flag = 0;
		}
		reg <<= 1;
		if(byte & 0x80) {
			reg|=1;
		}
		byte <<= 1;
		if(flag) {
			reg ^= poly;
		}
	}
	return reg;
	
}

uint8_t crc16(uint16_t word) {	
	uint8_t byte1 = word >> 8;
	uint8_t byte2 = word & 0xff;
	crc8(byte1);
	return crc8(byte2);		
}