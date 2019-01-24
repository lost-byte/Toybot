/*
 * uart_cli.h
 *
 * Created: 24.01.2019 15:48:35
 *  Author: Kholodkov
 */ 


#ifndef UART_CLI_H_
#define UART_CLI_H_

#include "editor.h"

int cli_printprg(prg_t *prg);
int cli_addline(char code, unsigned char arg);
int cli_insline(char code, unsigned char arg);
int cli_delline(void);
int cli_setcursor(unsigned char num);
int cli_newprg(void);
int cli_goprg(void);

#endif /* UART_CLI_H_ */