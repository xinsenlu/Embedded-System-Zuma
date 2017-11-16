#ifndef LED_H
#define LED_H
#include <p32xxxx.h>


#define NeoPin PORTEbits.RE2
#define NeoNum 60
#define InitNum 20
#define ALL_OUT 0x00
#define ALL_IN  0xFF
#define NeoInitial TRISEbits.TRISE2

#define bit_test(D,i) ((D>>i) & 1)
unsigned char NeoGreen [NeoNum];
unsigned char NeoBlue [NeoNum];
unsigned char NeoRed [NeoNum];

int forehead;
int backhead;
#endif