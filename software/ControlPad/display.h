/*
 * display.h
 *
 *  Created on: 28 дек. 2018 г.
 *      Author: Kholodkov
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

void init_display(void);
void show_logo (void);

void draw_cmd_line(char cmd, unsigned char arg);
void draw_prg_list(prg_recrd_t *prg, unsigned char cursor_pos);

#endif /* DISPLAY_H_ */
