#include "MUSIC.h"

void MC_Config(){
	DDPCONbits.JTAGEN = 0;
	TRISD=0xff00;
	rush=1;
	initial=1;
	cancel=1;
	button=1;
	success=1;
	failure=1;

}
