#include"header.h"
extern int flag1;
extern int flag2;
extern char temp;
void EINT1_handler(void)__irq
{
		flag1^=1;       //On every call Toggles, Initialized with 0 in data segment.
		EXTINT=2;          //To clear the EINT1 intr flag.(So next time also the Interrupt will trigger)
		VICVectAddr=0;          //To finish the ISR execution
}
void UART0_handler(void)__irq
{
	flag2=1;
	temp=U0RBR;	   // Reading the data
	VICVectAddr=0;	  //Clearing the interrupt 
}
void config_eint0(void)
{
	VICIntSelect=0;      //No FIQ's
	VICVectCntl1=15|(1<<5);   //EINT1 number is 15
	VICVectAddr1=(u32)EINT1_handler;
	VICVectCntl0=6|(1<<5);   //UART0 enterrupt number is 6
	VICVectAddr0=(u32)UART0_handler;
	VICIntEnable|=(1<<15);		//EINT1 number is 15
	VICIntEnable|=(1<<6);	    //UART0 number is 6
}
void ent0_init(void)
{
	EXTPOLAR=0;    // All are ACTIVE LOW (Even though we are only using 1 interrupt)
	EXTMODE=2;  //External Interrupt 1 is EDGE TRIGGERED
	PINSEL0|=0x20000000 ;  // 3 because the pin functionality selection is 3rd P0.14/DCD1/EINT1.
	//Since we are using the switch 14 (GPIO pin P0.14) EINT1 is allocated 
}
void enable_uart0_interrupt(void)
{
	U0IER=1;   //only the receiver interrupt we need
}

