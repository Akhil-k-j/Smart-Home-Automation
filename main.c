#include"header.h"
#define SW1 ((IOPIN0>>14)&1)
#define SW2 ((IOPIN0>>15)&1)
#define SW3 ((IOPIN0>>16)&1)
#define LED1 (1<<17)
#define BULB (1<<18)
#define FAN (1<<19)
#define RDR ((U0LSR)&1)

int flag1;	   //Switch pressed omterupt
int flag2;	   //Uart0 intterupt 
char temp;	   //Input character from the bluetooth UART0 

int main()
{
		uart0_init(9600);  	//Must and should right at first since the PINSEL0 '=' we used.
		ent0_init();
		config_eint0();
		enable_uart0_interrupt();
        IODIR0=7<<17;				//1 LED(For indication), 1 Bulb, 1 FAN.
        IOSET0=7<<17;    		//Turning off in the first attempt itself.
L1:
        uart0_tx_string("\r\nBluetooth mode\r\n");
		uart0_tx_string("\r\nMenu:\r\n1)BULB ON\r\n2)BULB OFF\r\n3)FAN ON\r\n4)FAN OFF\r\n");
        while(1)
        {		
				lcd_cmd(0x80);
				lcd_string(" BLUETOOTH MODE");   						
			    if(flag1==1) //External interrupt for switch
				{  
						delay_ms(10);  //to avaoid the rubberband effect;
                        manual_mode();  //Upon return from this function, The flag value will be 0						
						flag1=flag2=temp=0;			
							goto L1;
                }
               	if(flag2==1) //Uart0 interrupt 
                {
                        switch(temp)
                        {
                                case '1':IOCLR0=BULB;break;
                                case '2':IOSET0=BULB;break;
								case '3':IOCLR0=FAN;break;
                                case '4':IOSET0=FAN;break;
                                default:uart0_tx_string("\r\nWrong option\r\n");
                        }
						flag2=0;
						uart0_tx_string("\r\nMenu:\r\n1)BULB ON\r\n2)BULB OFF\r\n3)FAN ON\r\n4)FAN OFF\r\n");
                }
		}
}
void manual_mode(void)
{
		u32 adc_out;
		float vout,temp;
		adc_init();
		lcd_init();
        uart0_tx_string("\r\nManual mode\r\n");
        IOCLR0=LED1;
		lcd_cmd(0x01);
        while(1)
        {
	//Since we are in manual mode we will print the room temperatur to the LCD as an additional feature.		 
	adc_out=adc_read(1); // channel 1 selected		    
	vout=(adc_out*3.3)/1023;
	temp=((vout-0.5)/0.01);
	lcd_cmd(0x80);
	lcd_string("  MANUAL MODE  ");
	lcd_cmd(0xC0);
	lcd_string("ROOM TEMP: ");
	lcd_float(temp);
	lcd_string("C");
	delay_ms(100);	//To avoid the flickering of the TEMP value every time.		 	
                if(flag1==0)
                {
                        IOSET0=LED1;            //To indicate the mode for the user
						lcd_cmd(0x01);
						delay_ms(100);  //To avoid the rubberband effect.
                        return;
                }
                else if(SW2==0)
                {
                        while(SW2==0);
                        if((IOSET0>>18)&1)
                        {
                                IOCLR0=BULB;    //ON BULB
                        }
                        else
                        {
                                IOSET0=BULB;    //OFF BULB
                        }
                }
                else if(SW3==0)
                {
                        while(SW3==0);
                        if((IOSET0>>19)&1)
                        {
                                IOCLR0=FAN;    //ON the FAN
                        }
                        else
                        {
                                IOSET0=FAN;    //OFF the fan
                        }
                }
        }
}


