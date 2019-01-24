/*
 * uart.c
 *
 * Created: 24.01.2019 14:37:03
 *  Author: Kholodkov
 */ 
#include <avr/io.h>
#include <avr/delay.h>

void uart_init(){
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	UCSR0C = (1<<UCSZ01); // 8n1
	UBRR0L = 51; // 9600
}

void uart_write(char *buf, unsigned char len){
	for (unsigned char i=0;i<len;i++){
		UDR0 = *buf;
		buf++;
		while(UCSR0A&(1<<TXC0)){
			_delay_ms(2);
		}
	}
}

void uart_read(char *buf, unsigned char timeout_ms){
	unsigned char to_counter = 0;
	while(to_counter<timeout_ms){
		if (UCSR0A&(1<<RXC0)){
			*buf = UDR0;
			buf++;
			to_counter=0;
		}else{
			_delay_ms(1);
			to_counter++;
		}
	}
}