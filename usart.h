#pragma once

extern char buffer[LINEBUFFER_LENGTH];

void USART_TX(char data );
void USART_TXS(char* s);
char USART_RX(void);
void USART_RXS(void);
void usart_init();

