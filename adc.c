#include "stdinc.h"

void ADC_Init(void) {
  
  // die Versorgungsspannung AVcc als Referenz w�hlen:
  ADMUX = (1<<REFS0);    
  
  // oder interne Referenzspannung als Referenz f�r den ADC w�hlen:
  // ADMUX = (1<<REFS1) | (1<<REFS0);
 
  // Bit ADFR ("free running") in ADCSRA steht beim Einschalten
  // schon auf 0, also single conversion
  ADCSRA = (1<<ADPS1) | (1<<ADPS0);     // Frequenzvorteiler
  ADCSRA |= (1<<ADEN);                  // ADC aktivieren
 
  /* nach Aktivieren des ADC wird ein "Dummy-Readout" empfohlen, man liest
     also einen Wert und verwirft diesen, um den ADC "warmlaufen zu lassen" */
 
  ADCSRA |= (1<<ADSC);                  // eine ADC-Wandlung 
  while (ADCSRA & (1<<ADSC) ) {}        // auf Abschluss der Konvertierung warten

  /* ADCW muss einmal gelesen werden, sonst wird Ergebnis der n�chsten
     Wandlung nicht �bernommen. */
  (void) ADCW;
}
 
/* ADC Einzelmessung */
uint16_t ADC_Read( uint8_t channel ) {
  // Kanal waehlen, ohne andere Bits zu beeinflu�en
  ADMUX = (ADMUX & ~(0x1F)) | (channel & 0x1F);
  ADCSRA |= (1<<ADSC);            // eine Wandlung "single conversion"
  while (ADCSRA & (1<<ADSC) ) {   // auf Abschluss der Konvertierung warten
  }
  return ADCW;                    // ADC auslesen und zur�ckgeben
}
 
/* ADC Mehrfachmessung mit Mittelwertbbildung */
/* beachte: Wertebereich der Summenvariablen */
uint16_t ADC_Read_Avg( uint8_t channel, uint8_t nsamples ) {
  uint32_t sum = 0;
  for (uint8_t i = 0; i < nsamples; ++i ) {
    sum += ADC_Read( channel );
  }
  return (uint16_t)( sum / nsamples );
}
