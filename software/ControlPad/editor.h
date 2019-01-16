/*
 * editor.h
 *
 * Created: 14.01.2019 21:16:40
 *  Author: Denis
 */ 


#ifndef EDITOR_H_
#define EDITOR_H_

/// Коды команд
#define CMD_FWD 'f'
#define CMD_BWD 'b'
#define CMD_LFT 'l'
#define CMD_RGT 'r'
#define CMD_FOR 'w'
#define CMD_HLD 'g'
#define CMD_NON 0

/// Структура однй строчки программы
struct _prg_record_t{
	char code;
	unsigned char arg;
};

typedef struct _prg_record_t prg_recrd_t;

struct _prg_t{
	prg_recrd_t *prg_rows;
	unsigned char len;
	unsigned char cur_pos;
};

typedef struct _prg_t prg_t;

extern prg_t programm;

// Вызывается в цикле после получения нового нажатия
void process_key(char key);

#endif /* EDITOR_H_ */