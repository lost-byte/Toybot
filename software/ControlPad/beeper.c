/*
 * beeper.c
 *
 * Created: 12.01.2019 22:19:47
 *  Author: Denis
 */ 
 #include <avr/io.h>
 #include <avr/interrupt.h>
 #include <util/delay.h>

 #include "pin_helper.h"
 #include "settings.h"

 void pwm_start(){
	 TCCR1A = (1<<COM1B1)|(1<<COM1B0)|(1<<WGM10);
	 TCCR1B = (1<<WGM13)|(1<<CS11);
	 OCR1B = 50;
	 OCR1A = 500UL;
 }

 void pwm_stop(){
	 TCCR1B = 0;
 }

 void pwm_amp_freq(char amp, unsigned short freq){
	 OCR1A = freq;
	 OCR1B = amp;
 }

 void blip_reg(){
	 pwm_start();
	 _delay_ms(100);
	 pwm_amp_freq(50,600UL);
	 _delay_ms(40);
	 pwm_amp_freq(50,490UL);
	 _delay_ms(30);
	 pwm_amp_freq(50,510UL);
	 _delay_ms(20);
	 pwm_amp_freq(50,490UL);
	 _delay_ms(30);
	 pwm_amp_freq(20,200UL);
	 _delay_ms(100);
	 pwm_amp_freq(70,700UL);
	 _delay_ms(40);
	 pwm_stop();
	 CLR(BEEPER);
 }

 void blip_err(){
	 pwm_start();
	 _delay_ms(100);
	 pwm_amp_freq(50,600UL);
	 _delay_ms(40);
	 pwm_amp_freq(50,490UL);
	 _delay_ms(30);
	 pwm_amp_freq(50,510UL);
	 _delay_ms(20);
	 pwm_amp_freq(50,490UL);
	 _delay_ms(30);
	 pwm_amp_freq(20,200UL);
	 _delay_ms(100);
	 pwm_amp_freq(70,700UL);
	 _delay_ms(40);
	 pwm_stop();
	 CLR(BEEPER);
 }

 void blip_enter(){
	 pwm_start();
	 _delay_ms(100);
	 pwm_amp_freq(50,600UL);
	 _delay_ms(40);
	 pwm_amp_freq(50,490UL);
	 _delay_ms(30);
	 pwm_amp_freq(50,510UL);
	 _delay_ms(20);
	 pwm_amp_freq(50,490UL);
	 _delay_ms(30);
	 pwm_amp_freq(20,200UL);
	 _delay_ms(100);
	 pwm_amp_freq(70,700UL);
	 _delay_ms(40);
	 pwm_stop();
	 CLR(BEEPER);
 }