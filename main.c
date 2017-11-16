#include "LED.h"
#include "delay.h"
#include "CN.h"
#include "MUSIC.h"
#include "ball.h"
#include <plib.h>
#include <stdlib.h>
#include <time.h>
#include <sys/kmem.h>

/*define macros for LCD instructions */
#define LCD_IDLE 0x33 
#define LCD_2_LINE_4_BITS 0x28 
#define LCD_2_LINE_8_BITS 0x38 
#define LCD_DSP_CSR 0x0c 
#define LCD_CLR_DSP 0x01 
#define LCD_CSR_INC 0x06 
#define LCD_SFT_MOV 0x14
/*define macros for interfacing ports*/
#define RS   PORTAbits.RA6
#define E    PORTAbits.RA7
#define Data  PORTE

typedef unsigned char uchar;

int flag=0;

/* Function prototypes */
void MCU_init(void);
void LCD_init(void);
void LCD_putchar(uchar c); 
void LCD_puts(const uchar *s); 
void LCD_goto(uchar addr); 
void GenMsec(void);
void DelayUsec(uchar num); 
void DelayMsec(uchar num);

/*****************end of LCD.h**********************/
/************************************************************************ * LCD.c ************************************************************************/
//global variables

int isStart=0;
int isEND=0;
int isSHOOT=0;
//value
int acc=1;
int score;
int dir = 0;
int bias=0;
int ShootPoint=0;//flags
forehead=0;
int balls=0;
backhead=0;
//
uchar startStr1[] = "ZUMA"; 
const uchar startStr3[] = "START"; 
uchar startStr4[] = "Sad"; 
uchar startStr5[] = "AWESOME"; 
 uchar startStr2[15];
//random initialize
int r; 

//function call
void CN_ISR(void);
void CNConfig(void);
void Ball_Init(void);
void insert(int position);
int nearby(int position);
int leftfind(int position);
int rightfind(int position);
int equal(int position1, int position2);
void recover (int position1, int position2);

#pragma interrupt PWM_ISR ipl5 vector 8
void PWM_ISR()
{
  PR2 += acc;       //Change the peroid

  IFS0bits.T2IF = 0;
}


//interrupt
#pragma interrupt CN_ISR ipl6 vector 26
void CN_ISR (void){
  IEC1CLR=0x0001;
  button=0;
  if (readA!=START)
  {
    isStart=1;
    //Draw the color of ball
    HeadDraw();
    //opening
    unsigned int NeoPixel=0;
            while(NeoPixel < NeoNum) {
            NeoGreen[NeoPixel] = 0; NeoBlue[NeoPixel] = 0; NeoRed[NeoPixel] = 4; 
            NeoDraw();delay_ms(25);NeoPixel++;
            }
    delay_ms(100);
    NeoInit();
    //MUSIC
    initial=0;
    //balls
    Ball_Init();
    //forehead
    forehead=InitNum-1;
    //ballcount
    balls=19;
    //SCORE
    score=0;
    //RACE START:
    RS=0;
    LCD_goto(0x00); 
    RS=1;
    LCD_puts(startStr3);
    RS=0;
  }
  else if (readB!=END)
  {
    isEND=1;
  }
  else if (readC!=SHOOT)
  {
    if (isStart)
    {
      isSHOOT=1;
    //shootig ball color 
    //insert
    insert(ShootPoint);
    rush=0;
    //update
    forehead++;
    NeoDraw();
    delay_ms(50);
    int MeetPoint=ShootPoint;
    //collapse
    while(nearby(MeetPoint)){
      int start=lowerfind(MeetPoint);
      int end=higherfind(MeetPoint);
    int n=end-start+1;
      void recover(end, start);
      cancel=0;
      NeoDraw();
      delay_ms(50);
      MeetPoint=start;

      //value update
      forehead=forehead-n;
      score+=10*n;
    }
    
    }

        //score
    int A=score/10000;
    int B=score/1000;
    int C=score/100;
    int D=score/10;
    startStr2[0] = 'S';
    startStr2[1] = 'C';
    startStr2[2] = 'O';
    startStr2[3] = 'R';
    startStr2[4] = 'E';
    startStr2[6] = ':';
    startStr2[7] = ((int)A)+ 48;
    startStr2[8] = (int)(B-(A*10)) + 48;
    startStr2[9] = (int)(B-(A*10)) + 48;
    startStr2[10] = (int)(C-(B*10)) + 48;
    startStr2[10] = (int)(D-(C*10)) + 48;
    startStr2[11] = (int)(score-(D*10)) + 48; 
    RS=0;
    LCD_goto(0x40); 
    RS=1;
    LCD_puts(startStr2); 
    RS=0;
    //
    isSHOOT=0;
    //fresh the light
    HeadDraw();
  }
  else if (readD!=LEFT)
  {
        dir =1;
       PORTDbits.RD1 = dir;
       initPWM();
  }
  else if (readE!=RIGHT)
  {
        dir =0;
       PORTDbits.RD1 = dir;
       initPWM();
  }

  IFS1CLR=0x0001;
  IEC1SET=0x0001;
}
void recover (int positionH, int positionL){
  unsigned int NeoPixel;   
  int n= positionH- positionL+1;
   for (NeoPixel = positionH+1; NeoPixel < NeoNum; NeoPixel++)   
   {           
      NeoGreen[NeoPixel-n] = NeoGreen[NeoPixel];
      NeoBlue[NeoPixel-n] = NeoBlue[NeoPixel];
      NeoRed[NeoPixel-n] = NeoRed[NeoPixel];
   }
   for (NeoPixel = NeoNum-n; NeoPixel < NeoNum; NeoPixel++)   
   {           
      NeoGreen[NeoPixel] = 0;
      NeoBlue[NeoPixel] = 0;
      NeoRed[NeoPixel] = 0;
   }
}
void insert(int position){
   int NeoPixel;   
   for (NeoPixel = forehead; NeoPixel >position; NeoPixel--)   
   {           
      NeoGreen[NeoPixel+1] = NeoGreen[NeoPixel];
      NeoBlue[NeoPixel+1] = NeoBlue[NeoPixel];
      NeoRed[NeoPixel+1] = NeoRed[NeoPixel];
   }
   NeoGreen[position] = 0;
   NeoBlue[position] = 0;
   NeoRed[position] = 0; 
}
int equal(int position1, int position2){
  if (NeoGreen[position1] == NeoGreen[position2] &  NeoBlue[position1] == NeoBlue[position2] & NeoRed[position1] == NeoRed[position2])
  {
      return 1;

  }
  else{
      return 0;
  }
}
int nearby(int position){
    if (higherfind(position)-lowerfind(position)>1)
    {
      return 1;
    }
    else return 0;
}
int lowerfind(int position){
    int n=0;
  while(equal(position-n,position)){
        n++;
        if (position-n<backhead) break;
  }
  return position-n;
}
int higherfind(int position){
  int n=0;
  while(equal(position+n,position)){
        n++;
        if (position+n>forehead) break;
  }
  return n+position;
}





void Ball_Init(void){
      unsigned int NeoPixel=0;
            while(NeoPixel < InitNum) {
            r = rand(); 
            if (r%3==0){
            NeoGreen[NeoPixel] = 0; NeoBlue[NeoPixel] = 0; NeoRed[NeoPixel] = 4; 
            }
            else if (r%3==1)
            {
            NeoGreen[NeoPixel] = 4; NeoBlue[NeoPixel] = 0; NeoRed[NeoPixel] = 0; 
            }
            else
            {
            NeoGreen[NeoPixel] = 0; NeoBlue[NeoPixel] = 4; NeoRed[NeoPixel] = 0; 
            }
            NeoDraw();delay_ms(25);NeoPixel++;
            }
}



void main()
{   
   SYSTEMConfigPerformance(80000000);
   OSCSetPBDIV (OSC_PB_DIV_1);
   initPWM();
   MCU_init(); 
   LCD_init(); 
   CNConfig();
   TimerConfig();
   MC_Config();
   srand(time(NULL)); 
   NeoInitial=0;
   NeoInit ();   
   while(1)
   {      
      if(!isEND){

         if (isStart)
         {  
          //increase one ball per second
                        if(forehead < NeoNum) {
                                  NeoRotate(); 
                                  if (balls<=100)
                                  {
                                      r = rand(); 
                                      if (r%3==0){
                                      NeoGreen[0] = 0; NeoBlue[0] = 0; NeoRed[0] = 4; 
                                      }
                                      else if (r%3==1)
                                      {
                                      NeoGreen[0] = 4; NeoBlue[0] = 0; NeoRed[0] = 0; 
                                      }
                                      else
                                      {
                                      NeoGreen[0] = 0; NeoBlue[0] = 4; NeoRed[0] = 0; 
                                      }
                                      NeoDraw();delay_ms(500);

                                      balls++;
                                  }
                                  else
                                  {
                                      backhead++;
                                      NeoDraw();delay_ms(500);
                                  }

                                      forehead++;
                                                          if (forehead==backhead)
                                                          {
                                                            isEND=1;
                                                            //music
                                                            success=0;
                                                            RS=0;
                                                            LCD_goto(0x00); 
                                                            RS=1;
                                                            LCD_puts(startStr5);
                                                            RS=0;
                                                          }
                                                          if (isSHOOT)
                                                        {
                                                        }
                        }
                      else
                      {

                        isEND=1;
                        //music
                        failure=0;
                        //SAD STORY
                        RS=0;
                        LCD_goto(0x00); 
                        RS=1;
                        LCD_puts(startStr4);
                        RS=0;
                      }
         }
         else {//not start yet
          //show "JI ZUMA
          RS=0;
          LCD_goto(0x00); 
          RS=1;
          LCD_puts(startStr1);
          RS=0;
         }
}
  else {
        isStart=0;
        isSHOOT=0;
        isEND=0;
        score=0;
        forehead=0;
        backhead=0;
        balls=0;
                               RS=0;
                        LCD_goto(0x00); 
                        RS=1;
                        LCD_puts(startStr1);
                        RS=0;
      }
   isEND=0;

}
}

/* initialize the PIC32 MCU */ 
void MCU_init() {
/* setup I/O ports to connect to the LCD module */ 
      DDPCONbits.JTAGEN = 0;
      TRISA=0xff00;
      TRISE=0xff00;
/* setup Timer to count for 1 us and 1 ms */ 
      T2CONbits.ON=0;
      T2CONbits.TCS=0;
      T2CONbits.TCKPS=1;
      T2CONbits.TGATE=0;
      TMR2=0;
      PR2=4;
      T4CONbits.ON=0;
      T4CONbits.TCS=0;
      T4CONbits.TCKPS=1;
      T4CONbits.TGATE=0;
      TMR4=0;
      PR4=624;
/* Configure Timer interrupts */ 
/* enable global and individual interrupts */
 }
/* initialize the LCD module */ 
void LCD_init() {
DelayMsec(15);
RS = 0;
Data = LCD_IDLE;
DelayMsec(5);
Data = LCD_IDLE; 
DelayUsec(100);
Data = LCD_IDLE;
DelayMsec(5);
Data = LCD_IDLE; 
DelayUsec(100); 
LCD_putchar(LCD_2_LINE_4_BITS);
DelayUsec(40); 
LCD_putchar(LCD_DSP_CSR);
DelayUsec(40);
LCD_putchar(LCD_CLR_DSP);
DelayMsec(5); 
LCD_putchar(LCD_CSR_INC);
}



/* Send one byte c (instruction or data) to the LCD */ 
void LCD_putchar(uchar c) {
E = 1;
Data = c;
E = 0;
E = 1;
Data <<= 4;
E = 0;
}
//sending higher nibble //producing falling edge on E
//sending lower nibble through higher 4 ports //producing falling edge on E
/* Display a string of characters *s by continuously calling LCD_putchar() */ 
void LCD_puts(const uchar *s) {
      while(*s){
            LCD_putchar(*s++);
            DelayUsec(40);
      }
}
/* go to a specific DDRAM address addr */ 
void LCD_goto(uchar addr) {
      RS=0;
      LCD_putchar(0x80+addr);
      DelayUsec(40);
 }
/* configure timer SFRs to generate num us delay*/ 
void DelayUsec(uchar num) {
      PR2=50*num-1;
      T2CONbits.ON=1;
      while(!IFS0bits.T2IF);
      IFS0CLR=0x000100;
      T2CONINV=0x8000;
      
      }
/* configure timer SFRs to generate 1 ms delay*/ 
void GenMsec()
{
      PR4=50000;
      T4CONbits.ON=1;
      while(!IFS0bits.T4IF);
      IFS0CLR=0x010000;
      T4CONINV=0x8000;
}
/* Call GenMsec() num times to generate num ms delay*/ 
void DelayMsec(uchar num) {
      uchar i;
      for (i=0; i<num; i++) {
      GenMsec(); }
      
}
/*************end of LCD.c**************/
