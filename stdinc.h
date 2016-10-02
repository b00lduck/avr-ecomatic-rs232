#pragma once
#include <avr/io.h>
#include <stdlib.h> 
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include <avr/eeprom.h>

#define LINEBUFFER_LENGTH 64
#define MAXCMDLEN 16

#define SUCCESS 0
#define ERROR	1
#define CHECKSUM_ERROR	2


#define EEPROM_SIZE 1024

#define MACOFFSET (EEPROM_SIZE-6)









