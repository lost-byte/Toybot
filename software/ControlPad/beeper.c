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

 #include "beeper.h"

 const sample_t snd_ok[11]={
	 {500,1000,10},
	 {400,800,20},
	 {300,600,30},
	 {250,500,40},
	 {200,400,40},
	 {250,500,40},
	 {200,400,40},
	 {250,500,40},
	 {200,400,30},
	 {150,300,20},
	 {100,200,10},
 };

 const sound_t blip_ok= {11,snd_ok};

 const sample_t snd_err[11]={
	 {500,1000,10},
	 {400,800,20},
	 {300,600,30},
	 {250,700,40},
	 {200,600,40},
	 {250,800,40},
	 {200,600,40},
	 {250,800,40},
	 {200,600,30},
	 {150,900,20},
	 {100,1000,10},
 };

 const sound_t blip_err= {11,snd_err};

 const sample_t snd_enter[14]={
	 {500,1000,10},
	 {400,800,20},
	 {300,600,30},
	 {250,550,40},
	 {200,450,40},
	 {250,550,40},
	 {200,450,40},
	 {250,550,40},
	 {200,450,30},
	 {250,550,40},
	 {200,450,30},
	 {250,550,40},
	 {200,450,30},
	 {150,300,20},
	 {100,200,10},
 };

 const sound_t blip_enter= {11,snd_enter};

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

 void beep_delay_ms(unsigned char ms){
	for (unsigned char i=0;i<ms;i++){
		_delay_us(990);
	}
 }

 void blip(sound_t sound){
	 pwm_start();
	 for (unsigned char step=0;step<sound.len;step++){
		pwm_amp_freq(sound.samples[step].duty,sound.samples[step].freq);
		beep_delay_ms(sound.samples[step].period);
	 }
	 pwm_stop();
	 CLR(BEEPER);
 }

 