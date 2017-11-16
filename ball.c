#include "ball.h"
void HeadBit (int Bit)
{
   if (Bit == 1)
            { HeadPin=1; 
                   asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
                   asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
                   asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
                   asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
                   asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
                   asm("nop");
                   //51
                   HeadPin=0;
                  asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
                  asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
                  asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
                  asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
                  asm("nop");asm("nop");asm("nop");
                  }   
             else
                  { HeadPin=1; 
                   asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
                   asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
                   asm("nop");asm("nop");asm("nop");
                  //24
                    HeadPin=0;
                   asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
                   asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
                   asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
                   asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
                   asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
                   asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
                   } 
}

void HeadDraw (void)
{
   r2=rand();
    if (r2%3==0){
            HeadGreen = 0; HeadBlue = 0; HeadRed = 4; 
    }
    else if (r2%3==1){
            HeadGreen = 4; HeadBlue = 0; HeadRed = 0; 
    }
    else{
            HeadGreen = 0; HeadBlue= 4; HeadRed = 0; 
    }
   unsigned int NeoPixel;
   signed int BitCount;
   for (NeoPixel = 0; NeoPixel < HeadNum; NeoPixel++)
   {    
      for (BitCount = 7; BitCount >= 0; BitCount--)      
         HeadBit(bit_test(HeadGreen, BitCount));      
      for (BitCount = 7; BitCount >= 0; BitCount--)           
         HeadBit(bit_test(HeadRed, BitCount));            
      for (BitCount = 7; BitCount >= 0; BitCount--)      
         HeadBit(bit_test(HeadBlue, BitCount));      
   }
   HeadPin=0;
}