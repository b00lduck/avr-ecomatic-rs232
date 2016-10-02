#pragma once

#include <avr/io.h>

#define SYSCLK 14745600

inline void delayloop16 (uint16_t count);
inline void delay_long (uint8_t count);

#define SBI(port,bit) port |= (1<<bit)
#define CBI(port,bit) port &= ~(1<<bit)



