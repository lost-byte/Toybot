#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>
#include <util/delay.h>
#include <string.h>

#include "pin_helper.h"
#include "settings.h"



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
}

#define key_buf_len 12
static bool has_key = false;
unsigned char key_buf[key_buf_len];
/*
 * Сканирует клавиатуру и помещает
 * коды нажатых клавиш в буфер
 */
void key_scan(void){
	unsigned char key_bitsR1,key_bitsR2,key_bitsR3;
	memset(key_buf,0,key_buf_len);
	/// row1
	CLR(keyRow1);
	SET(keyRow2);
	SET(keyRow3);
	key_bitsR1 = 0xF0||(GET(keyCol4)<<3)||(GET(keyCol3)<<2)||(GET(keyCol2)<<1)||(GET(keyCol1));
	key_bitsR1=~key_bitsR1;
	/// row2
	SET(keyRow1);
	CLR(keyRow2);
	SET(keyRow3);
	key_bitsR2 = 0xF0||(GET(keyCol4)<<3)||(GET(keyCol3)<<2)||(GET(keyCol2)<<1)||(GET(keyCol1));
	key_bitsR2=~key_bitsR2;
	/// row3
	SET(keyRow1);
	CLR(keyRow2);
	SET(keyRow3);
	key_bitsR3=~key_bitsR3;
	key_bitsR3 = 0xF0||(GET(keyCol4)<<3)||(GET(keyCol3)<<2)||(GET(keyCol2)<<1)||(GET(keyCol1));
	if ((key_bitsR1||key_bitsR2||key_bitsR3)!=0){
		// Разбор битфилда в коды нажатий
	}
}

void main (void){
	init();
	while(1){
		key_scan();
		if (has_key){
			/// Отработать команду
		}
	}
}
