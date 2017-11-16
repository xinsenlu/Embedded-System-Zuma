#include "delay.h"



#pragma interrupt T1_ISR ipl7 vector 4

void T1_ISR(void){
	IFS0bits.T1IF = 0;
}

void TimerConfig(){
	INTCONbits.MVEC=1;
	asm("ei");

	IPC1SET=0x0000001c;
	IFS0CLR=0x00000010;
	IEC0SET=0x00000010;


	T1CONbits.ON=0;
	T1CONbits.TCS=0;
	T1CONbits.TCKPS=1;
	T1CONbits.TGATE=0;

	TMR1=0;
	PR1=9999;
	T1CONbits.ON=1;


}

void delay_1ms(void){
	TimerConfig();
	while(!IFS0bits.T1IF);
}

void delay_ms(int num){
	while(num--){
	delay_1ms();
}
}

