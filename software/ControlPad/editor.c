/*
 * editor.c
 *
 * Created: 13.01.2019 10:59:12
 *  Author: Denis
 *  ��������� ���� ������,
 * ��������� �������� ��� �������� �� ������.
 */ 

#include "editor.h"
#include "display.h"
#include "beeper.h"

/// ��������� ���������
#define STATE_CMD 1
#define STATE_ARG 2
#define STATE_EDT 3

static char state=STATE_CMD; // ��������� ����� ���������
static unsigned char agr_sym_no = 0;
static char arg_buf[3];
static char curr_cmd=CMD_NON;
static char curr_arg=1;

prg_t programm;

void add_line(){
	programm.prg_rows[programm.len].code=curr_cmd;
	programm.prg_rows[programm.len].arg=curr_arg;
	programm.len++;
	draw_prg_list(&programm);
}

void ins_line(){
	// �������� ��������� ������� �� ������ �� �������� ������� ����
	for (unsigned char i=programm.len;i>programm.cur_pos;i--){
		programm.prg_rows[i]=programm.prg_rows[i-1];
	}
	programm.prg_rows[programm.cur_pos+1].code=curr_cmd;
	programm.prg_rows[programm.cur_pos+1].arg=curr_arg;
	programm.len++;
	draw_prg_list(&programm);
}

// ������� ��������� ������� ���� � ������ edt
void delete_line(){
	// �������� ��������� ������� �� ������ ������ �� �������� ������� �����
	for (unsigned char i=programm.cur_pos+1;i<programm.len;i++){
		programm.prg_rows[i-1]=programm.prg_rows[i];
	}
	programm.len--;
	draw_prg_list(&programm);
}

// ������ ��������� ������� � ����
void move_cursor(char dir){
	if (dir){
		(programm.cur_pos<programm.len)?(programm.cur_pos++):(programm.cur_pos=0);
	}else{
		(programm.cur_pos!=0)?(programm.cur_pos--):(programm.cur_pos=programm.len);
	}
}

// ������� ��� ���������
void clear_prg(){
	programm.len=0;
	programm.cur_pos=0;
}

void set_cmd(char cmd){
	if (cmd!=curr_cmd){
		// ���� ����� �������
		curr_cmd = cmd;
		curr_arg = 1;
		draw_cmd_line(cmd,curr_arg);
	}else{
		// ���������� ���������
		curr_arg++;
		draw_cmd_line(cmd,curr_arg);
	}

}

int process_cmd_key(char key){
	switch(key){
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
		set_cmd(key);
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
		/// ������� ��������� ������� � ���������
		add_line();
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
		add_line();
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
		blip(blip_err);
		break;
	case 1:
		blip(blip_ok);
		break;
	case 2:
		blip(blip_enter);
		break;
	}
}