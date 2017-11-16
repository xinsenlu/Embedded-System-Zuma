#ifndef BALL_H
#define BALL_H
#include <p32xxxx.h>
#include <plib.h>
#include <stdlib.h>
#include <time.h>

#define HeadPin PORTEbits.RE1
#define HeadNum 8
#define HeadInitial TRISEbits.TRISE1
#define bit_test(D,i) ((D>>i) & 1)
void HeadBit (int Bit);
void HeadDraw (void);
int r2;
int HeadGreen; 
int HeadBlue; 
int HeadRed; 



#endif