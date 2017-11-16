#include <stdlib.h>
#include "LED.h"
#include "delay.h"

unsigned long int bitflip(unsigned char b);

// transmit the ws2812 led
void ws2812_send(int Num) {
    int j;
    long int val;
    // the WS2812 wants bits in the order of:
    // GGGGGGGGRRRRRRRRBBBBBBBB
    // but I want to work in the opposite order. so i'm going to flip
    // the bits around and do some shifting so my order is
    // BBBBBBBBRRRRRRRRGGGGGGGG
    // with the most significant bit on the far right. so the RGB value
    // of 128 64 32, which normally would be:
    // R : 0b10000000
    // G : 0b01000000
    // B : 0b00100000
    // will become:
    // BBBBBBBBRRRRRRRRGGGGGGGG
    // 000001000000000100000010
    val = (bitflip(NeoBlue[Num]) << 16) + (bitflip(NeoRed [Num]) << 8) + (bitflip(NeoGreen [Num]));

    // now begin shifting them over one at a time
    for(j = 0; j < 24; j++) {
        // depending on if the currently viewed bit is 1 or 0
        // the pin will stay high for different times

        if (val & 1 == 1) {
            // if it is a 1, let it stay higher a bit longer
            NeoPin = 1;
              asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
              asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
              asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
              asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
              asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
              asm("nop");
              //51
            NeoPin = 0;
              asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
              asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
        } else {
            // but a 0 should go high and then low as fast as possible
            NeoPin = 1;
            asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
            asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
            asm("nop");asm("nop");asm("nop");
            NeoPin = 0;
            asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
            asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
            asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
            asm("nop");asm("nop");asm("nop");
        }
        
        // and then right shift to get the next bit
        val = val >> (unsigned char)1;
    }
}

// reverse the bits in a char
unsigned long int bitflip(unsigned char b) {
   b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
   b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
   b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
   return (unsigned long int)b;
}
void NeoInit (void)
{
   unsigned int NeoPixel;
   for (NeoPixel = 0; NeoPixel < NeoNum; NeoPixel++)   
   {
      if (NeoPixel < 10)
         { NeoGreen[NeoPixel] = 0; NeoBlue[NeoPixel] = 0; NeoRed[NeoPixel] = 0; }
      else if ((NeoPixel >= 10) & (NeoPixel < 20))
         { NeoGreen[NeoPixel] = 0; NeoBlue[NeoPixel] = 0; NeoRed[NeoPixel] = 0; }
      else if ((NeoPixel >= 20) & (NeoPixel < 30))
         { NeoGreen[NeoPixel] = 0; NeoBlue[NeoPixel] = 0; NeoRed[NeoPixel] = 0; }
      else if ((NeoPixel >= 30) & (NeoPixel < 40))
         { NeoGreen[NeoPixel] = 0; NeoBlue[NeoPixel] = 0; NeoRed[NeoPixel] = 0; }
      else if ((NeoPixel >= 40) & (NeoPixel < 50))
         { NeoGreen[NeoPixel] = 0; NeoBlue[NeoPixel] = 0; NeoRed[NeoPixel] = 0; }
      else if ((NeoPixel >= 50) & (NeoPixel < NeoNum))
         { NeoGreen[NeoPixel] = 0; NeoBlue[NeoPixel] = 0; NeoRed[NeoPixel] = 0; }      
   }
}
void NeoEnd (void)
{
   unsigned int NeoPixel;
   for (NeoPixel = 0; NeoPixel < NeoNum; NeoPixel++)   
   {
      if (NeoPixel < 10)
         { NeoGreen[NeoPixel] = 4; NeoBlue[NeoPixel] = 4; NeoRed[NeoPixel] = 4; }
      else if ((NeoPixel >= 10) & (NeoPixel < 20))
         { NeoGreen[NeoPixel] = 4; NeoBlue[NeoPixel] = 4; NeoRed[NeoPixel] = 4; }
      else if ((NeoPixel >= 20) & (NeoPixel < 30))
         { NeoGreen[NeoPixel] = 4; NeoBlue[NeoPixel] = 4; NeoRed[NeoPixel] = 4; }
      else if ((NeoPixel >= 30) & (NeoPixel < 40))
         { NeoGreen[NeoPixel] = 4; NeoBlue[NeoPixel] = 4; NeoRed[NeoPixel] = 4; }
      else if ((NeoPixel >= 40) & (NeoPixel < 50))
         { NeoGreen[NeoPixel] = 4; NeoBlue[NeoPixel] = 4; NeoRed[NeoPixel] = 4; }
      else if ((NeoPixel >= 50) & (NeoPixel < NeoNum))
         { NeoGreen[NeoPixel] = 4; NeoBlue[NeoPixel] = 4; NeoRed[NeoPixel] = 4; }      
   }
}
void NeoDraw (void)
{
   unsigned int NeoPixel=0;
   signed int BitCount;
   while(NeoPixel < NeoNum)
   {    
       ws2812_send(NeoPixel);
         NeoPixel++;   
   }
   NeoPin=0;
}
void NeoRotate (void)
{
   int NeoPixel;   
   for (NeoPixel = forehead; NeoPixel >=0; NeoPixel--)   
   {           
      NeoGreen[NeoPixel+1] = NeoGreen[NeoPixel];
      NeoBlue[NeoPixel+1] = NeoBlue[NeoPixel];
      NeoRed[NeoPixel+1] = NeoRed[NeoPixel];
   }
   NeoGreen[0] = 0;
   NeoBlue[0] = 0;
   NeoRed[0] = 0; 
}
void startgame(void){
   unsigned int NeoPixel=0;
   while(NeoPixel < NeoNum) {
      NeoGreen[NeoPixel] = 0; NeoBlue[NeoPixel] = 0; NeoRed[NeoPixel] = 4; 
      NeoDraw();delay_ms(100);NeoPixel++;
   }
   NeoInit();
   NeoDraw();
   delay_ms(25);
}