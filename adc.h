#pragma once

void ADC_Init(void);
uint16_t ADC_Read( uint8_t channel );
uint16_t ADC_Read_Avg( uint8_t channel, uint8_t nsamples );