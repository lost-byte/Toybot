/*
 * beeper.h
 *
 * Created: 12.01.2019 22:21:46
 *  Author: Denis
 */ 


#ifndef BEEPER_H_
#define BEEPER_H_

struct _sample_t{
	unsigned short duty;
	unsigned short freq;
	unsigned short period;
};

typedef struct _sample_t sample_t;

struct _sound_t{
	unsigned char len;
	const sample_t *samples;
};

typedef struct _sound_t sound_t;

/// {250,500} - 1 KHz 1/2-duty

extern const sound_t blip_ok;
extern const sound_t blip_err;
extern const sound_t blip_enter;

void blip(sound_t sound);

#endif /* BEEPER_H_ */