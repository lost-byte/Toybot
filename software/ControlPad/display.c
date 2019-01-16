/*
* display.c
*
*  Created on: 26 дек. 2018 г.
*      Author: lost-byte
*/
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>

#include "u8g2.h"
#include "pin_helper.h"
#include "settings.h"

#include "editor.h"

/// Точка (верхняя левая) вывода вводимой строки
/// Высота командной строки 20
#define cmd_line_x (62)
#define cmd_line_y (11)
/// Глиф команды 20x20
#define cmd_gliph_w (20)
#define cmd_gliph_h (20)

#define cmd_arg_x (cmd_line_x+cmd_gliph_w)
#define cmd_arg_y (cmd_line_y+cmd_gliph_h-2)


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
		PIN_OUT(LCD_RW);

		SET(LCD_E);
		SET(LCD_RESET);
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
		SET(LCD_CS);
		if(arg_int){
			SET(LCD_E);
			}else{
			CLR(LCD_E);
		}
		break;
		
		case U8X8_MSG_GPIO_CS:				// CS (chip select) pin: Output level in arg_int
		/*
		if(arg_int){
			//SET(LCD_CS);
			//set_cs = 1;
			(set_cs2)?(SET(LCD_CS)):(CLR(LCD_CS));
		}else{
			//CLR(LCD_CS);
			//set_cs = 0;
			(!set_cs1)?(SET(LCD_CS)):(CLR(LCD_CS));
		}
		*/
		CLR(LCD_CS);
		if(arg_int){
			SET(LCD_E);
			}else{
			CLR(LCD_E);
		}
		if(arg_int){
			SET(LCD_E);
			}else{
			CLR(LCD_E);
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
		/*
		case U8X8_MSG_GPIO_CS1:				// CS1 (chip select) pin: Output level in arg_int
		if(arg_int){
			SET(LCD_CS);
			//set_cs1 = 1;
			}else{
			CLR(LCD_CS);
			//set_cs1 = 0;
		}
		break;
		case U8X8_MSG_GPIO_CS2:				// CS2 (chip select) pin: Output level in arg_int
		if(arg_int){
			CLR(LCD_CS);
			//set_cs2 = 1;
			}else{
			SET(LCD_CS);
			//set_cs2 = 0;
		}
		break;
		*/
		default:
		if (u8x8_avr_delay(u8x8, msg, arg_int, arg_ptr))	// check for any delay msgs
		return 1;
		u8x8_SetGPIOResult(u8x8, 1);			// default return value
		break;
	}
	return 1;
}

void init_display(void){
	u8g2_Setup_mt12232_122x32_f(&u8g2, U8G2_R0, u8x8_byte_sed1520, u8x8_gpio_and_delay);
	u8g2_InitDisplay(&u8g2);
	//u8g2_SetFlipMode(&u8g2,1);
	//u8g2.u8x8.cad_cb(&u8g2, U8X8_MSG_CAD_START_TRANSFER, 0, NULL);
	//u8x8_cad_SendCmd(&u8g2, 0xA1);
	//u8g2.u8x8.cad_cb(&u8g2, U8X8_MSG_CAD_END_TRANSFER, 0, NULL);
	//u8g2.u8x8.x_offset = 40;
	//u8g2.clip_x0=10;
	u8g2_SetPowerSave(&u8g2, 0);

}

/// Глифы команд
/// 20x20
/// Назад
static const unsigned char backward20x20[] U8X8_PROGMEM ={
	0x00, 0x00, 0x00, 0x80, 0x3f, 0x00, 0x80, 0x3f, 0x00, 0x80, 0x3f, 0x00,
	0x80, 0x3f, 0x00, 0x80, 0x3f, 0x00, 0x80, 0x3f, 0x00, 0x80, 0x3f, 0x00,
	0x80, 0x3f, 0x00, 0x80, 0x3f, 0x00, 0x80, 0x3f, 0x00, 0x80, 0x3f, 0x00,
	0xf0, 0xff, 0x01, 0xe0, 0xff, 0x00, 0xc0, 0x7f, 0x00, 0x80, 0x3f, 0x00,
	0x00, 0x1f, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00 };

/// Вперед
static const unsigned char forward20x20[] U8X8_PROGMEM= {
	0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x1f, 0x00,
	0x80, 0x3f, 0x00, 0xc0, 0x7f, 0x00, 0xe0, 0xff, 0x00, 0xf0, 0xff, 0x01,
	0x80, 0x3f, 0x00, 0x80, 0x3f, 0x00, 0x80, 0x3f, 0x00, 0x80, 0x3f, 0x00,
	0x80, 0x3f, 0x00, 0x80, 0x3f, 0x00, 0x80, 0x3f, 0x00, 0x80, 0x3f, 0x00,
	0x80, 0x3f, 0x00, 0x80, 0x3f, 0x00, 0x80, 0x3f, 0x00, 0x00, 0x00, 0x00 };

/// Налево
static const unsigned char left20x20[] U8X8_PROGMEM= {
	0x80, 0x00, 0x00, 0xc0, 0x00, 0x00, 0xe0, 0x00, 0x00, 0xf0, 0x1f, 0x00,
	0xf8, 0x7f, 0x00, 0xfc, 0xff, 0x00, 0xf8, 0xff, 0x00, 0xf0, 0xff, 0x01,
	0xe0, 0xf8, 0x01, 0xc0, 0xf0, 0x01, 0x80, 0xf0, 0x01, 0x00, 0xf0, 0x01,
	0x00, 0xf0, 0x01, 0x00, 0xf0, 0x01, 0x00, 0xf0, 0x01, 0x00, 0xf0, 0x01,
	0x00, 0xf0, 0x01, 0x00, 0xf0, 0x01, 0x00, 0xf0, 0x01, 0x00, 0x00, 0x00 };

/// Направо
static const unsigned char right20x20[] U8X8_PROGMEM= {
	0x00, 0x10, 0x00, 0x00, 0x30, 0x00, 0x00, 0x70, 0x00, 0x80, 0xff, 0x00,
	0xe0, 0xff, 0x01, 0xf0, 0xff, 0x03, 0xf0, 0xff, 0x01, 0xf8, 0xff, 0x00,
	0xf8, 0x71, 0x00, 0xf8, 0x30, 0x00, 0xf8, 0x10, 0x00, 0xf8, 0x00, 0x00,
	0xf8, 0x00, 0x00, 0xf8, 0x00, 0x00, 0xf8, 0x00, 0x00, 0xf8, 0x00, 0x00,
	0xf8, 0x00, 0x00, 0xf8, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00 };

/// 8x8 для листинга
/// Назад
static const unsigned char backward8x8[] U8X8_PROGMEM ={
	0x00, 0x10, 0x10, 0x10, 0x7c, 0x38, 0x10, 0x00 };

/// Вперед
static const unsigned char forward8x8[] U8X8_PROGMEM= {
	0x00, 0x10, 0x38, 0x7c, 0x10, 0x10, 0x10, 0x00 };


/// Налево
static const unsigned char left8x8[] U8X8_PROGMEM= {
	0x08, 0x0c, 0x3e, 0x6c, 0x48, 0x40, 0x40, 0x00 };

/// Направо
static const unsigned char right8x8[] U8X8_PROGMEM= {
	 0x10, 0x30, 0x7c, 0x36, 0x12, 0x02, 0x02, 0x00 };


/// массив указателей на глифы команд
static const unsigned char* cmd_gliphs20x20[] = {0,left20x20,forward20x20,right20x20,left20x20,backward20x20,right20x20}; 
static const unsigned char* cmd_gliphs8x8[] = {0,left8x8,forward8x8,right8x8,left8x8,backward8x8,right8x8}; 

void show_logo (void){
	//u8g2_SetFont(&u8g2, u8g2_font_robot_de_niro_tf);
	//u8g2_font_5x8_t_cyrillic
	
	u8g2_SetFont(&u8g2, /*u8g2_font_cu12_t_cyrillic*/ u8g2_font_5x8_tn );
	
	//u8g2_ClearBuffer(&u8g2);
	
	//u8g2_DrawUTF8(&u8g2, 0, 21, "Привет!");
	//u8g2_DrawXBMP(&u8g2,50,8,16,16,left);
	//u8g2_DrawXBMP(&u8g2,66,8,16,16,forward);
	//u8g2_DrawXBMP(&u8g2,82,8,16,16,backward);
	//u8g2_DrawXBMP(&u8g2,98,8,16,16,right);


	u8g2_SendBuffer(&u8g2);
}

void print_key(char key){
	char str[2]={0,0};
	str[0] = key;
	u8g2_ClearBuffer(&u8g2);
	u8g2_DrawUTF8(&u8g2,6,21, str);
	u8g2_SendBuffer(&u8g2);
}

/// Выводит листинг программы с позиции старт 
/// и положением курсорв cur
/// моноширинный шрифт 5x8
void list_pgr(char *prg, char start, char cur){
	
}

static char arg_str[4];
/// Печатает символ команды в области ввода и числовой аргумент
void draw_cmd_line(char cmd, unsigned char arg){
	u8g2_DrawXBMP(&u8g2,cmd_line_x,cmd_line_y,cmd_gliph_w, cmd_gliph_h,cmd_gliphs20x20[cmd]);
	//itoa(arg,arg_str,10);
	sprintf(arg_str,"%03u",arg);
	//u8g2_SetFont(&u8g2, u8g2_font_10x20_mn );
	u8g2_SetFont(&u8g2, u8g2_font_profont22_tn ); // неплохо
	//u8g2_SetFont(&u8g2, u8g2_font_helvB18_tn ); // великоват, нули не перечеркнуты
	u8g2_DrawStr(&u8g2, cmd_arg_x, cmd_arg_y, arg_str);
	u8g2_SendBuffer(&u8g2);
}

/// Выводит/стирает значок режима CMD
void draw_mode_cmd(char yes){

}

/// Выводит/стирает значок NUM
void draw_mode_num(char yes){

}

/// Выводит/стирает значок Edit
void draw_mode_edt(char yes){

}

/// Печатает лист программы и курсор
/// листинг выводится в 2 колонки по 4 записи
#define MAX_COL 2
#define MAX_ROW 4
#define PRGREC_W 25
#define PRGREC_H 8
void draw_prg_list(prg_t *prg){
	u8g2_SetFont(&u8g2, /*u8g2_font_cu12_t_cyrillic*/ u8g2_font_5x8_tn );
	/// По колонкам
	for (char col=0;col<MAX_COL;col++){
		// По строчкам
		for (char row=0;row<MAX_ROW;row++){
			/// Напечатать в нужном месте символ курсора
			if ((MAX_ROW*col+row)==cursor_pos){
				u8g2_DrawStr(&u8g2,col*PRGREC_W,row*PRGREC_H+PRGREC_H,">");
			}
			u8g2_DrawXBMP(&u8g2, col*PRGREC_W,row*PRGREC_H,cmd_gliphs8x8[prg->code]);
			sprintf(arg_str,"%03u",prg->arg);
			u8g2_DrawStr(&u8g2, col*PRGREC_W+9,row*PRGREC_H+PRGREC_H,arg_str);
		}
	}
}