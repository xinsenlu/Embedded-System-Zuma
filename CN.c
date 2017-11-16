#include "CN.h"




void CNConfig(){
	INTCONbits.MVEC=1; 
	asm("di");
	CNCON=0x8000; 
	CNEN = 0x98003;
    CNPUE = 0x98003;
	TRISDbits.TRISD13=1;
	TRISDbits.TRISD6=1;
	TRISDbits.TRISD7=1;
	TRISCbits.TRISC13=1;
	TRISCbits.TRISC14=1;
	readA=START;
	readB=END;
	readC=SHOOT;
	readD=LEFT;
	readE=RIGHT; 
	IPC6SET=0x00140000; 
	IPC6SET=0x00030000; 
	IFS1CLR=0x0001; 
	IEC1SET=0x0001;
 asm("ei"); 
}
void initPWM() 
{
	 OC1CON = 0x0000;      //stop OC1 module
     OC1RS = 0xfe00;          //initialize duty cycle register
     OC1R = 0xfe00;           //initialize OC1R register for the first time
     OC1CON = 0x0006;      //OC1 16-bit, Timer 2, in PWM mode w/o FP
     PR2 = 0xffe4;
     IFS0CLR = 0x00000100; //clear Timer 2 interrupt
     IEC0SET = 0x00000100; //enable Timer 2 interrupt
     IPC2SET = 0x0000000F; //Timer 2 interrupt priority 3, subpriority 3
     T2CONSET = 0x8000;    //start Timer 2
     OC1CONSET = 0x8000;   //enable OC1 module for PWM generation

}



