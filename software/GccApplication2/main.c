/*
 * GccApplication2.c
 *
 * Created: 01.01.2019 14:00:44
 * Author : Denis
 */ 

#include <avr/io.h>
#include <util/delay.h>

#include "settings.h"
#include "pin_helper.h"

//команды
#define COM_DISPLAY_ON       0xaf               //включает жкд
#define COM_DISPLAY_OFF      0xae               //выключает жкд
#define COM_START_LINE(x)    (0xc0&(0x1f&(x)))  //определяет верхнюю строку жкд
#define COM_ADC_SELECT_OFF   0xa0               //прямое соответствие адреса и позиции
#define COM_ADC_SELECT_ON    0xa1               //обратное соответствие адреса и позиции
#define COM_STATIC_DRIVE_ON  0xa5               //статический режим управления
#define COM_STATIC_DRIVE_OFF 0xa4               //обычное управление
#define COM_DUTY_SELECT_ON   0xa9               //выбор мультиплекса
#define COM_CLEAR_RMW        0xee               //снятие флага RMW
#define COM_SELECT_RMW       0xe0               //установка флага RMW
#define COM_RESET            0xe2               //строка и страница сбрасывается в 0

#define PAGE0 0xb8
#define PAGE1 0xb9
#define PAGE2 0xba
#define PAGE3 0xbb

void LCDBusOut(void){
	PIN_OUT(LCD_D0);
	PIN_OUT(LCD_D1);
	PIN_OUT(LCD_D2);
	PIN_OUT(LCD_D3);
	PIN_OUT(LCD_D4);
	PIN_OUT(LCD_D5);
	PIN_OUT(LCD_D6);
	PIN_OUT(LCD_D7);

	CLR(LCD_D0);
	CLR(LCD_D1);
	CLR(LCD_D2);
	CLR(LCD_D3);
	CLR(LCD_D4);
	CLR(LCD_D5);
	CLR(LCD_D6);
	CLR(LCD_D7);
}

void LCDBusIn(void){
	PIN_IN(LCD_D0);
	PIN_IN(LCD_D1);
	PIN_IN(LCD_D2);
	PIN_IN(LCD_D3);
	PIN_IN(LCD_D4);
	PIN_IN(LCD_D5);
	PIN_IN(LCD_D6);
	PIN_IN(LCD_D7);
	/*
	SET(LCD_D0);
	SET(LCD_D1);
	SET(LCD_D2);
	SET(LCD_D3);
	SET(LCD_D4);
	SET(LCD_D5);
	SET(LCD_D6);
	SET(LCD_D7);
	*/
	CLR(LCD_D0);
	CLR(LCD_D1);
	CLR(LCD_D2);
	CLR(LCD_D3);
	CLR(LCD_D4);
	CLR(LCD_D5);
	CLR(LCD_D6);
	CLR(LCD_D7);
}

void LCDBusW(unsigned char arg){
	unsigned char bit;
	bit = 0x1&(arg>>0);
	if (bit) SET(LCD_D0) else CLR(LCD_D0);
	bit = 0x1&(arg>>1);
	if (bit) SET(LCD_D1) else CLR(LCD_D1);
	bit = 0x1&(arg>>2);
	if (bit) SET(LCD_D2) else CLR(LCD_D2);
	bit = 0x1&(arg>>3);
	if (bit) SET(LCD_D3) else CLR(LCD_D3);
	bit = 0x1&(arg>>4);
	if (bit) SET(LCD_D4) else CLR(LCD_D4);
	bit = 0x1&(arg>>5);
	if (bit) SET(LCD_D5) else CLR(LCD_D5);
	bit = 0x1&(arg>>6);
	if (bit) SET(LCD_D6) else CLR(LCD_D6);
	bit = 0x1&(arg>>7);
	if (bit) SET(LCD_D7) else CLR(LCD_D7);
}

unsigned char LCDBusR(){
	unsigned char bit=0;
	bit|=GET(LCD_D7);
	bit<<=1;
	bit|=GET(LCD_D6);
	bit<<=1;
	bit|=GET(LCD_D5);
	bit<<=1;
	bit|=GET(LCD_D4);
	bit<<=1;
	bit|=GET(LCD_D3);
	bit<<=1;
	bit|=GET(LCD_D2);
	bit<<=1;
	bit|=GET(LCD_D1);
	bit<<=1;
	bit|=GET(LCD_D0);
	return bit;
}

unsigned char LCDCommonR(){
	unsigned char res;
	LCDBusIn();
	SET(LCD_RW);
	_delay_us(10);
	CLR(LCD_E);
	_delay_us(10);
	res = LCDBusR();
	_delay_us(10);
	SET(LCD_E);
	CLR(LCD_RW);
	LCDBusOut();
	return res;
}

void LCDCommonW(unsigned char arg){
	CLR(LCD_RW);
	_delay_us(10);
	CLR(LCD_E);
	_delay_us(10);
	LCDBusW(arg);
	_delay_us(50);
	SET(LCD_E);
	_delay_ms(10);
}

void LCDCommand(unsigned char arg){
	//LCDWaitBusy();
	CLR(LCD_A0);
	LCDCommonW(arg);
	SET(LCD_A0);
}

void LCDData(unsigned char arg){
	//LCDWaitBusy();
	
	LCDCommonW(arg);
}

unsigned char LCDDataR(){
	unsigned char res;
	SET(LCD_A0);
	res = LCDCommonR();
	return res;
}

unsigned char LCDStatus(){
	unsigned char res;
	CLR(LCD_A0);
	res = LCDCommonR();
	return res;
}

void LCDWaitBusy(){
	unsigned char status = 0;
	do {
		status = LCDStatus();
	} while (status&0x80);
}



int main(void)
{
	PIN_OUT(LED2);
	PIN_OUT(LED1)

	LCDBusOut();
	
	PIN_OUT(LCD_CS);
	PIN_OUT(LCD_A0);
	PIN_OUT(LCD_RESET);
	PIN_OUT(LCD_E);
	PIN_OUT(LCD_RW);

	PIN_OUT(LCD_LED);
	SET(LCD_E);
	SET(LCD_LED);

	_delay_ms(10);
	SET(LCD_RESET);
	_delay_ms(10);
	//CLR(LCD_RESET);
	//_delay_ms(100);

	SET(LCD_CS);
	LCDCommand(COM_CLEAR_RMW);
	LCDCommand(COM_STATIC_DRIVE_OFF);
	LCDCommand(COM_DUTY_SELECT_ON);
	LCDCommand(COM_DISPLAY_ON);
	LCDCommand(COM_ADC_SELECT_OFF);
	LCDCommand(COM_RESET);
	LCDCommand(COM_START_LINE(0));


	LCDCommand(PAGE0);
	LCDDataR();
	LCDCommand(0);
	LCDDataR();
	
	LCDData(0xb1);
	LCDData(0x02);
	LCDData(0x04);
	LCDData(0x08);
	LCDData(0x10);
	LCDData(0x20);
	LCDData(0x40);
	LCDData(0x80);
	
	
	CLR(LCD_CS);
	LCDCommand(COM_CLEAR_RMW);
	LCDCommand(COM_STATIC_DRIVE_OFF);
	LCDCommand(COM_DUTY_SELECT_ON);
	LCDCommand(COM_DISPLAY_ON);
	LCDCommand(COM_ADC_SELECT_OFF);
	LCDCommand(COM_RESET);
	LCDCommand(COM_START_LINE(0));
	
	LCDCommand(PAGE2);
	LCDDataR();
	LCDCommand(0x0a);
	LCDDataR();
	
	LCDData(0xAA);
	LCDData(0x55);
	LCDData(0xAA);
	LCDData(0x55);
	LCDData(0xAA);
	LCDData(0x55);
	LCDData(0xAA);
	LCDData(0x55);
	
	SET(LCD_CS);
	volatile unsigned char status = LCDStatus();

	LCDCommand(PAGE0);
	LCDDataR();
	LCDCommand(1);
	LCDDataR();

	volatile unsigned char test = LCDDataR();
	

    while (1) 
    {
	/*
		_delay_ms(50);
		SET(LED2);
		SET(LED1);
		_delay_ms(50);
		CLR(LED2);
		SET(LED1);
		_delay_ms(50);
		SET(LED2);
		CLR(LED1);
		*/
		int addr;
		LCDCommand(PAGE0);
		LCDDataR();
		LCDCommand(1);
		for (addr=0;addr<80;addr++){
			LCDData(addr);
		}
		LCDCommand(PAGE1);
		LCDDataR();
		LCDCommand(1);
		for (addr=0;addr<80;addr++){
			LCDData(addr);
		}
		LCDCommand(PAGE2);
		LCDDataR();
		LCDCommand(1);
		for (addr=0;addr<80;addr++){
			LCDData(addr);
		}
		LCDCommand(PAGE3);
		LCDDataR();
		LCDCommand(1);
		for (addr=0;addr<80;addr++){
			LCDData(addr);
		}
    }
}

