/*
 * editor.c
 *
 * Created: 13.01.2019 10:59:12
 *  Author: Denis
 *  ��������� ���� ������,
 * ��������� �������� ��� �������� �� ������.
 */ 

 #define STAGE_CMD 1
 #define STAGE_ARG 2

 #define MODE_ADD 1
 #define MODE_INS 2
 #define MODE_REP 3

 char stage=STAGE_CMD; // ��������� ����� ���������

 void process_cmd_key(char key){
	switch(key){
		case 0x0d:
		break;
	}
 }

 void process_arg_key(char key){
	switch(key){
	case 0x0d:
		/// ��������� ����
		/// ������� ��������� ������� � ���������
		/// � ������  MODE_ADD � �����
		/// � ������ MODE_INS � ������� �� ��������
		/// � ������ MODE_REP ������ ������ ��� ��������
		break;
	}
 }

 // ���������� � ����� ����� ��������� ������ �������
 void process_key(char key){
	switch(stage){
	case STAGE_CMD:
		process_cmd_key(key);
		break;
	case STAGE_ARG:
		process_arg_key(key);
		break;
	}
 }