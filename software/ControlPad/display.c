/*
 * display.c
 *
 *  Created on: 26 дек. 2018 г.
 *      Author: lost-byte
 */
#include <avr/io.h>
#include <util/delay.h>
#include "pin_helper.h"
#include "settings.h"
#include "u8g2.h"

u8g2_t u8g2;



uint8_t u8x8_avr_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
	uint8_t cycles;

	switch(msg)
	{
		case U8X8_MSG_DELAY_NANO:     // delay arg_int * 1 nano second
			// At 20Mhz, each cycle is 50ns, the call itself is slower.
			break;
		case U8X8_MSG_DELAY_100NANO:    // delay arg_int * 100 nano seconds
			// Approximate best case values...
#define CALL_CYCLES 26UL
#define CALC_CYCLES 4UL
#define RETURN_CYCLES 4UL
#define CYCLES_PER_LOOP 4UL

			cycles = (100UL * arg_int) / (P_CPU_NS * CYCLES_PER_LOOP);

			if(cycles > CALL_CYCLES + RETURN_CYCLES + CALC_CYCLES)
				break;

			__asm__ __volatile__ (
			"1: sbiw %0,1" "\n\t" // 2 cycles
			"brne 1b" : "=w" (cycles) : "0" (cycles) // 2 cycles
			);
			break;
		case U8X8_MSG_DELAY_10MICRO:    // delay arg_int * 10 micro seconds
			for(int i=0 ; i < arg_int ; i++)
				_delay_us(10);
			break;
		case U8X8_MSG_DELAY_MILLI:      // delay arg_int * 1 milli second
			for(int i=0 ; i < arg_int ; i++)
				_delay_ms(1);
			break;
		default:
			return 0;
	}
	return 1;
}

/*
uint8_t u8x8_avr_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
	// Re-use library for delays

	switch(msg)
	{
		case U8X8_MSG_GPIO_AND_DELAY_INIT:  // called once during init phase of u8g2/u8x8


		case U8X8_MSG_GPIO_RESET:     // Reset pin: Output level in arg_int
			if(arg_int)
				//DISPLAY_RESET_PORT |= (1<<DISPLAY_RESET_PIN);
			else
				//DISPLAY_RESET_PORT &= ~(1<<DISPLAY_RESET_PIN);
			break;
		default:
			if (u8x8_avr_delay(u8x8, msg, arg_int, arg_ptr))	// check for any delay msgs
				return 1;
			u8x8_SetGPIOResult(u8x8, 1);      // default return value
			break;
	}
	return 1;
}
*/



uint8_t u8x8_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
  switch(msg)
  {

    case U8X8_MSG_GPIO_AND_DELAY_INIT:	// called once during init phase of u8g2/u8x8
    	PIN_OUT(LCD_D0);
    	PIN_OUT(LCD_D1);
    	PIN_OUT(LCD_D2);
    	PIN_OUT(LCD_D3);
    	PIN_OUT(LCD_D4);
    	PIN_OUT(LCD_D5);
    	PIN_OUT(LCD_D6);
    	PIN_OUT(LCD_D7);
    	PIN_OUT(LCD_CS);
    	PIN_OUT(LCD_A0);
    	PIN_OUT(LCD_RESET);
    	PIN_OUT(LCD_E);
      break;
      /*							// can be used to setup pins
    case U8X8_MSG_DELAY_NANO:			// delay arg_int * 1 nano second
      break;
    case U8X8_MSG_DELAY_100NANO:		// delay arg_int * 100 nano seconds
      break;
    case U8X8_MSG_DELAY_10MICRO:		// delay arg_int * 10 micro seconds
      break;
    case U8X8_MSG_DELAY_MILLI:			// delay arg_int * 1 milli second
      break;
    case U8X8_MSG_DELAY_I2C:				// arg_int is the I2C speed in 100KHz, e.g. 4 = 400 KHz
      break;							// arg_int=1: delay by 5us, arg_int = 4: delay by 1.25us
      */
    case U8X8_MSG_GPIO_D0:				// D0 or SPI clock pin: Output level in arg_int
    //case U8X8_MSG_GPIO_SPI_CLOCK:
    	if (arg_int){
    		SET(LCD_D0);
    	}else{
    		CLR(LCD_D0);
    	}
      break;
    case U8X8_MSG_GPIO_D1:				// D1 or SPI data pin: Output level in arg_int
    //case U8X8_MSG_GPIO_SPI_DATA:
    	if (arg_int){
    		SET(LCD_D1);
    	}else{
    		CLR(LCD_D1);
    	}
      break;
    case U8X8_MSG_GPIO_D2:				// D2 pin: Output level in arg_int
    	if (arg_int){
    		SET(LCD_D2);
    	}else{
    		CLR(LCD_D2);
    	}
      break;
    case U8X8_MSG_GPIO_D3:				// D3 pin: Output level in arg_int
    	if(arg_int){
    		SET(LCD_D3);
    	}else{
    		CLR(LCD_D3);
    	}
      break;
    case U8X8_MSG_GPIO_D4:				// D4 pin: Output level in arg_int
    	if (arg_int){
    		SET(LCD_D4);
    	}else{
    		CLR(LCD_D4);
    	}
      break;
    case U8X8_MSG_GPIO_D5:				// D5 pin: Output level in arg_int
    	if(arg_int){
    		SET(LCD_D5);
    	}else{
    		CLR(LCD_D5);
    	}
      break;
    case U8X8_MSG_GPIO_D6:				// D6 pin: Output level in arg_int
    	if (arg_int){
    		SET(LCD_D6);
    	}else{
    		CLR(LCD_D6);
    	}
      break;
    case U8X8_MSG_GPIO_D7:				// D7 pin: Output level in arg_int
    	if(arg_int){
    		SET(LCD_D7);
    	}else{
    		CLR(LCD_D7);
    	}
      break;
    case U8X8_MSG_GPIO_E:				// E/WR pin: Output level in arg_int
    	if(arg_int){
    		SET(LCD_E);
    	}else{
    		CLR(LCD_E);
    	}
      break;
    case U8X8_MSG_GPIO_CS:				// CS (chip select) pin: Output level in arg_int
    	if(arg_int){
			SET(LCD_CS);
		}else{
			CLR(LCD_CS);
		}
      break;
    case U8X8_MSG_GPIO_DC:				// DC (data/cmd, A0, register select) pin: Output level in arg_int
    	if(arg_int){
    		SET(LCD_A0);
    	}else{
    		CLR(LCD_A0);
    	}
      break;
    case U8X8_MSG_GPIO_RESET:			// Reset pin: Output level in arg_int
    	if(arg_int){
    		SET(LCD_RESET);
    	}else{
    		CLR(LCD_RESET);
    	}
      break;
//    case U8X8_MSG_GPIO_CS1:				// CS1 (chip select) pin: Output level in arg_int
//    	if(arg_int){
//    		SET(LCD_CS);
//    	}else{
//    		CLR(LCD_CS);
//    	}
//      break;
//    case U8X8_MSG_GPIO_CS2:				// CS2 (chip select) pin: Output level in arg_int
//    	if(arg_int){
//    		CLR(LCD_CS);
//    	}else{
//    		SET(LCD_CS);
//    	}
      break;
    default:
    	if (u8x8_avr_delay(u8x8, msg, arg_int, arg_ptr))	// check for any delay msgs
    					return 1;
      u8x8_SetGPIOResult(u8x8, 1);			// default return value
      break;
  }
  return 1;
}

void init_display(void){
	u8g2_Setup_sed1520_122x32_1(&u8g2, U8G2_R0, u8x8_byte_sed1520, u8x8_gpio_and_delay);
	u8g2_InitDisplay(&u8g2);

	u8g2_ClearBuffer(&u8g2);
	u8g2_SetFont(&u8g2, u8g2_font_4x6_tn);
	u8g2_DrawStr(&u8g2, 1, 18, "U8g2 on AVR");
	u8g2_SendBuffer(&u8g2);

}

static const unsigned char logo[] U8X8_PROGMEM = {
		0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
		0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
		0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
		0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
		0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
		0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
		0xff,0xff,0xff,0x00,0x00,0xff,0xff,0xff,
		0xff,0xff,0xff,0x00,0x00,0xff,0xff,0xff,
		0xff,0xff,0xff,0x00,0x00,0xff,0xff,0xff,
		0xff,0xff,0xff,0x00,0x00,0xff,0xff,0xff,
		0xff,0xff,0xff,0x00,0x00,0xff,0xff,0xff,
		0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
		0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
		0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
		0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
		0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
		0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
		0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
		0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
		0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
		0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
		0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
		0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
		0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
		0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
		0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
		0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
		0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
		0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
		0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
		0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
		0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
};

void show_logo (void){
	u8g2_DrawXBMP(&u8g2,0,0,64,32,logo);
}
