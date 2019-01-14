#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>

#include "pin_helper.h"
#include "settings.h"
#include "display.h"
#include "beeper.h"


void init(void){
	// Ряды клавиатуры - выходы, активный 0
	PIN_OUT(keyRow1);
	PIN_OUT(keyRow2);
	PIN_OUT(keyRow3);
	SET(keyRow1);
	SET(keyRow2);
	SET(keyRow3);
	// Колонки - входы с подтяжкой, 1 - клавиша нажата
	PIN_IN(keyCol1);
	PIN_IN(keyCol2);
	PIN_IN(keyCol3);
	PIN_IN(keyCol4);
	SET(keyCol1);
	SET(keyCol2);
	SET(keyCol3);
	SET(keyCol4);

	//Светодиоды
	PIN_OUT(LED1);
	PIN_OUT(LED2);
	PIN_OUT(LED3);
	PIN_OUT(LED4);

	PIN_OUT(LCD_LED);
	SET(LCD_LED);

	PIN_OUT(BEEPER);

	init_display();
	show_logo();

}


/*
 * Сканирует клавиатуру и помещает
 * коды нажатых клавиш в буфер
 */
char key_scan(void){
	unsigned char key_bitsR1,key_bitsR2,key_bitsR3;
	unsigned short key_bits;
	//memset(key_buf,0,key_buf_len);
	/// row1
	SET(keyRow1);
	SET(keyRow2);
	CLR(keyRow3);
	_delay_ms(10);
	key_bits |= !GET(keyCol4);
	key_bits<<=1;
	key_bits |= !GET(keyCol3);
	key_bits<<=1;
	key_bits |= !GET(keyCol2);
	key_bits<<=1;
	key_bits |= !GET(keyCol1);
	key_bits<<=1;
	/// row2
	SET(keyRow1);
	CLR(keyRow2);
	SET(keyRow3);
	_delay_ms(10);
	key_bits |= !GET(keyCol4);
	key_bits<<=1;
	key_bits |= !GET(keyCol3);
	key_bits<<=1;
	key_bits |= !GET(keyCol2);
	key_bits<<=1;
	key_bits |= !GET(keyCol1);
	key_bits<<=1;
	/// row3
	CLR(keyRow1);
	SET(keyRow2);
	SET(keyRow3);
	_delay_ms(10);
	key_bits |= !GET(keyCol4);
	key_bits<<=1;
	key_bits |= !GET(keyCol3);
	key_bits<<=1;
	key_bits |= !GET(keyCol2);
	key_bits<<=1;
	key_bits |= !GET(keyCol1);
	//key_bits<<=1;
	
	// Разбор битфилда в коды нажатий
	switch(key_bits){
		case 0x01:
			return '1';
		case 0x02:
			return '2';
		case 0x04:
			return '3';
		case 0x08:
			return 'C';
		case 0x10:
			return '4';
		case 0x20:
			return '5';
		case 0x40:
			return '6';
		case 0x80:
			return '0';
		case 0x100:
			return '7';
		case 0x200:
			return '8';
		case 0x400:
			return '9';
		case 0x800:
			return 0x0d; //Enter
		default:
			return 0;

	}
}

int main (void){
	char key=0;
	init();
	//pwm_start();
	SET(LED1);
	
	while(1){
		key = key_scan();
		if (key){
			
			blip_reg();

			/// Отработать команду
			print_key(key);

			
		}
		/*
		_delay_ms(200);
		SET(LED2);
		SET(LED1);
		_delay_ms(200);
		CLR(LED2);
		SET(LED1);
		_delay_ms(200);
		SET(LED2);
		CLR(LED1);
		_delay_ms(200);
		CLR(LED2);
		CLR(LED1);
		*/
		TGL(LED1);
	}
}
