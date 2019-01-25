/*
 * uart_cli.c
 *
 * Created: 24.01.2019 13:39:24
 *  Author: Kholodkov
 *  CLI интерфейс к платформе
 */ 
 #include <string.h>
 #include <stdio.h>

 #include "uart_cli.h"
 #include "editor.h"
 #include "uart.h"

 static char rxbuf[128];
 static char txbuf[16];
// Описание протокола
// Коды: f,b,r,l - вперед, назад, вправо, влево, зарезервировано за инструкциями программы

// Управление:
// p - печать листинга программы
// с NN - установка "курсора" на строку № NN
// d - удаление строки в позиции курсора
// i (строка программы) - вставить строку в позицию ПОСЛЕ курсора, курсор встает на новую строку
// a (строка программы) - вставить строку в конец программы
// n (new) - очистка программы
// g (go) - запуск программы

// отклик платформы:
// ок\n - успех
// err\n - ошибка
// # (с пробелом без перевода строки) - приглашение к вводу

int cli_check_ok(){
	// успехом считается последовательность символов "ok/n# " (5 символов)
	unsigned char anslen = strlen(rxbuf);
	return ~(strcmp(rxbuf+anslen-5,"ok/n# ")==0);
}

/*
void cli_parse_prg(prg_t prg){
	unsigned char anslen = strlen(rxbuf);
	*(rxbuf+anslen-5)=0;  /// обрезать приглашение
	/// Все до приглашения является листингом программы
	char code;
	unsigned char arg;
	unsigned char symbls=0;
	char  *scanbuf = rxbuf;
	while(symbls>0){}
		symbls = sscanf(scanbuf,"%c %u\n",code,arg);
		scanbuf += symbls;
	}
}

// Заказывает у платформы листинг программы, возвращает структуру prg_t
int cli_printprg(prg_t *prg){
	sprintf(txbuf,"p\n");
	uart_write(txbuf,strlen(txbuf));
	uart_read(rxbuf,100);   /// тайм-аут 100 мс
	if (cli_check_ok()){
		cli_parse_prg(prg);
		return 1;
	}else{
		return 0;
	}
}
*/

int cli_addline(char code, unsigned char arg){
	sprintf(txbuf,"a %c %u\n",code,arg);
	uart_write(txbuf,strlen(txbuf));
	uart_read(rxbuf,100);
	if (cli_check_ok()){
		return 1;
	}else{
		return 0;
	}
}

int cli_insline(char code, unsigned char arg){
	sprintf(txbuf,"i %c %u\n",code,arg);
	uart_write(txbuf,strlen(txbuf));
	uart_read(rxbuf,100);
	if (cli_check_ok()){
		return 1;
	}else{
		return 0;
	}
}

int cli_delline(void){
	sprintf(txbuf,"d\n");
	uart_write(txbuf,strlen(txbuf));
	uart_read(rxbuf,100);
	if (cli_check_ok()){
		return 1;
	}else{
		return 0;
	}
}

int cli_setcursor(unsigned char num){
	sprintf(txbuf,"c %u\n",num);
	uart_write(txbuf,strlen(txbuf));
	uart_read(rxbuf,100);
	if (cli_check_ok()){
		return 1;
	}else{
		return 0;
	}
}

int cli_newprg(void){
	sprintf(txbuf,"n\n");
	uart_write(txbuf,strlen(txbuf));
	uart_read(rxbuf,100);
	if (cli_check_ok()){
		return 1;
	}else{
		return 0;
	}
}

int cli_goprg(){
	sprintf(txbuf,"g\n");
	uart_write(txbuf,strlen(txbuf));
	uart_read(rxbuf,100);
	if (cli_check_ok()){
		return 1;
	}else{
		return 0;
	}
}
