#include <lpc21xx.h>
#include <string.h>

typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef signed  int s32;
typedef signed short s16;
typedef signed char s8;

void delay_s(unsigned int);
void delay_ms(unsigned int);

void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void lcd_string(char *);
void lcd_init(void);
void lcd_float(float);
void lcd_integer(int);
void lcd_float(float);
void lcd_hexa(int );

void uart0_tx_float(float);
void uart0_init(u32 );
void uart0_tx(u8 );
u8 uart0_rx(void);
void uart0_tx_string(s8 *);
void uart0_tx_integer(int);
void uart0_rx_string(u8 *,u8);

   /*
void config_ext_interrupt(void);
void en_uart0_interrupt(void);
void config_vic_interrupt(void);
	*/


///////LED TOGGLE////////
void config_vic_for_eint0(void);
void config_eint0(void);



		   
u32 adc_read(u8);
void adc_init(void);


void ent0_init(void);
void manual_mode(void);
void config_eint0(void);
void enable_uart0_interrupt(void);

u32 mcp3204_read(u8 ch_num);
void spi0_init(void);
u8 spi0(u8 data);
