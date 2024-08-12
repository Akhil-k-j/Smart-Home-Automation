#include"header.h"
#define DONE ((ADDR>>31)&1)
void adc_init(void)
{
	PINSEL1|=0x15400000;
	ADCR=0x00200400;
}
u32 adc_read(u8 ch_num)
{	
	u32 result=0;			  // variable to store the data
	ADCR|=(1<<ch_num);       // Selecting the channel number
	ADCR|=1<<24;			   //Start the conversion
	while(DONE==0);  //When DONE flag become 1 conversion completed
	ADCR^=1<<24;          //stop the conversion
	ADCR^=(1<<ch_num);	  //deselect the channel
	result=(ADDR>>6)&0x3FF;		//copy the converted result in the range of 0 to 1023
	return result;			  //returning the variable which contain the result.
}
