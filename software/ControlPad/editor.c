/*
 * editor.c
 *
 * Created: 13.01.2019 10:59:12
 *  Author: Denis
 *  ��������� ���� ������,
 * ��������� �������� ��� �������� �� ������.
 */ 

#include "display.h"
#include "beeper.h"

/// ��������� ���������
#define STATE_CMD 1
#define STATE_ARG 2
#define STATE_EDT 3

/// ���� ������
#define CMD_FWD 'f'
#define CMD_BWD 'b'
#define CMD_LFT 'l'
#define CMD_RGT 'r'
#define CMD_FOR 'w'
#define CMD_HLD 'g'
#define CMD_NON 0

static char state=STATE_CMD; // ��������� ����� ���������
static unsigned char agr_sym_no = 0;
static char arg_buf[3];
static char cmd;

// ������ ��������� ������� � ����
void move_cursor(char dir){

}

// ������� ��������� ������� ���� � ������ edt
void delete_line(){

}

void set_cmd(char cmd){
	if (cmd==CMD_NON){
		// ���� ����� �������
	}else{
		// ��������� �������
	}

}

int process_cmd_key(char key){
	switch(key){
	case 1:
		set_cmd(CMD_FOR);
		return 1;
	case 2:
		set_cmd(CMD_FWD);
		return 1;
	case 3:
		set_cmd(CMD_HLD);
		return 1;
	case 4:
		set_cmd(CMD_LFT);
		return 1;
	case 5:
		set_cmd(CMD_BWD);
		return 1;
	case 6:
		set_cmd(CMD_RGT);
		return 1;
	case 9:
		/// ���� ������� ������� - ������� � ����� ����� ��������� ���������
		state = STATE_ARG;
		return 2;
	case 0:
		// � ������ ������� ��� ������� � ����� ��������������
		state = STATE_EDT;
		return 2;
	case 0x0d:
		// ��������� ���� �������
		return 2;
	default:
		return 0;
	}
}

int process_arg_key(char key){
	switch(key){
	case 'C':
		/// ������� ��������� �����, ���� ���� ���� ��������� - ������� � ����� cmd
		return 1;
	case 0x0d:
		/// ��������� ����
		/// ������� ��������� ������� � ���������
		return 2;
	default:
		return 0;
	}
}

int process_edt_key(char key){
	switch(key){
	// ������ 2,5 �������� ��������� ��������� �� ����
	case '2':
		move_cursor(0);
		return 1;
	case '5':
		move_cursor(1);
		return 1;
	case 'C':
		// ������� ������ ��������� ��� ��������
		delete_line();
		return 1;
	case '0':
		/// ����� �� ������ ��������� ��� ���������
		return 1;
	case 0x0d:
		// ��������� ��������� �������
		state = STATE_CMD;
		return 2;
	default:
		return 0;
	}
}

// ���������� � ����� ����� ��������� ������ �������
void process_key(char key){
	int res=0;
	switch(state){
	case STATE_CMD:
		res = process_cmd_key(key);
		break;
	case STATE_ARG:
		res = process_arg_key(key);
		break;
	case STATE_EDT:
		res = process_edt_key(key);
		break;
	}
	switch (res){
	case 0:
		blip_err();
		break;
	case 1:
		blip_ok();
		break;
	case 2:
		blip_enter();
		break;
	}
}