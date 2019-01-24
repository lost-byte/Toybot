/*
 * uart_cli.c
 *
 * Created: 24.01.2019 13:39:24
 *  Author: Kholodkov
 *  CLI ��������� � ���������
 */ 
 #include <string.h>
 #include <stdio.h>

 #include "uart_cli.h"
 #include "editor.h"
 #include "uart.h"

 static char rxbuf[128];
 static char txbuf[16];
// �������� ���������
// ����: f,b,r,l - ������, �����, ������, �����, ��������������� �� ������������ ���������

// ����������:
// p - ������ �������� ���������
// � NN - ��������� "�������" �� ������ � NN
// d - �������� ������ � ������� �������
// i (������ ���������) - �������� ������ � ������� ����� �������, ������ ������ �� ����� ������
// a (������ ���������) - �������� ������ � ����� ���������
// n (new) - ������� ���������
// g (go) - ������ ���������

// ���������� � ��������� ������� ���������, ���������� ��������� prg_t
int cli_printprg(prg_t *prg){
	sprintf(txbuf,"p\n");
	uart_write(txbuf,strlen(txbuf));
	uart_read(rxbuf,100);   /// ����-��� 100 ��
	return 1;
}

int cli_addline(char code, unsigned char arg){
	sprintf(txbuf,"a %c %u\n",code,arg);
	uart_write(txbuf,strlen(txbuf));
	return 1;
}

int cli_insline(char code, unsigned char arg){
	sprintf(txbuf,"i %c %u\n",code,arg);
	uart_write(txbuf,strlen(txbuf));
	return 1;
}

int cli_delline(void){
	sprintf(txbuf,"d\n");
	uart_write(txbuf,strlen(txbuf));
	return 1;
}

int cli_setcursor(unsigned char num){
	sprintf(txbuf,"c %u\n",num);
	uart_write(txbuf,strlen(txbuf));
	return 1;
}

int cli_newprg(void){
	sprintf(txbuf,"n\n");
	uart_write(txbuf,strlen(txbuf));
	return 1;
}

int cli_goprg(){
	sprintf(txbuf,"g\n");
	uart_write(txbuf,strlen(txbuf));
	return 1;
}
