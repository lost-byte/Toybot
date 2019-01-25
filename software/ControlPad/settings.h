/*
 * settings.h
 *
 *  Created on: 26 дек. 2018 г.
 *      Author: Kholodkov
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_

#define P_CPU_NS (1000000000UL / F_CPU)

// Клавиатура: 3 ряда по 4 клавиши
#define keyRow1 D,7
#define keyRow2 D,6
#define keyRow3 D,5

#define keyCol1 C,0
#define keyCol2 C,1
#define keyCol3 C,2
#define keyCol4 C,3

// Двухцветные светодиоды
#define LED1 E,1
#define LED2 E,0
#define LED3 D,2
#define LED4 D,3

// Подсветка LCD
#define LCD_LED D,4

// интерфейс LCD
#define LCD_D0 A,5
#define LCD_D1 A,4
#define LCD_D2 A,3
#define LCD_D3 A,2
#define LCD_D4 B,4
#define LCD_D5 B,3
#define LCD_D6 B,2
#define LCD_D7 B,1

#define LCD_A0 B,0
#define LCD_RW A,0

#define LCD_E A,1
#define LCD_RESET A,6
#define LCD_CS A,7

// Beeper
#define BEEPER E,2

#define PRG_MAXROWS 64

#endif /* SETTINGS_H_ */
