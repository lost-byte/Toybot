/*
 * editor.h
 *
 * Created: 14.01.2019 21:16:40
 *  Author: Denis
 */ 


#ifndef EDITOR_H_
#define EDITOR_H_


/// ���� ������
#define CMD_FWD 'f'
#define CMD_BWD 'b'
#define CMD_LFT 'l'
#define CMD_RGT 'r'
#define CMD_FOR 'w'
#define CMD_HLD 'g'
#define CMD_NON 0

// ���������� � ����� ����� ��������� ������ �������
void process_key(char key);

#endif /* EDITOR_H_ */