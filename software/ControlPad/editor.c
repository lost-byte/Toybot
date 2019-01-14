/*
 * editor.c
 *
 * Created: 13.01.2019 10:59:12
 *  Author: Denis
 *  Принимает коды клавиш,
 * выполняет действия или сообщает об ошибке.
 */ 

 #define STAGE_CMD 1
 #define STAGE_ARG 2

 #define MODE_ADD 1
 #define MODE_INS 2
 #define MODE_REP 3

 char stage=STAGE_CMD; // состояние ввода программы

 void process_cmd_key(char key){
	switch(key){
		case 0x0d:
		break;
	}
 }

 void process_arg_key(char key){
	switch(key){
	case 0x0d:
		/// Завершить ввод
		/// подшить введенную строчку в программу
		/// в режиме  MODE_ADD в конец
		/// в режиме MODE_INS в позицию за курсором
		/// в режиме MODE_REP вместо строки под курсором
		break;
	}
 }

 // Вызывается в цикле после получения нового нажатия
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