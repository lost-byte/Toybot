/*
 * uart.h
 *
 * Created: 24.01.2019 14:38:54
 *  Author: Kholodkov
 */ 


#ifndef UART_H_
#define UART_H_

void uart_init(void);
void uart_write(char *buf, unsigned char len);
void uart_read(char *buf, unsigned char timeout);

#endif /* UART_H_ */