#ifndef PSG_H
#define PSG_H

#include "types.h"
#include <osbind.h>

/*----- YM2149 REGISTER VALUES -----
Refer to the YM2149 Application Manual.
*/
#define PSG_REG_SELECT_ADDRESS 0xFF8800
#define PSG_REG_WRITE_ADDRESS 0xFF8802

#define CHANNEL_A 0
#define CHANNEL_B 1
#define CHANNEL_C 2

#define CHANNEL_A_FINE 0
#define CHANNEL_A_COARSE 1
#define CHANNEL_B_FINE 2
#define CHANNEL_B_COARSE 3
#define CHANNEL_C_FINE 4
#define CHANNEL_C_COARSE 5
#define NOISE_FREQ 6
#define MIXER 7
#define A_LEVEL 8
#define B_LEVEL 9
#define C_LEVEL 10
#define ENV_FREQ_FINE 11
#define ENV_FREQ_COARSE 12
#define ENV_SHAPE 13

#define TONE_ON 1
#define NOISE_ON 1
#define TONE_OFF 0
#define NOISE_OFF 0

/*----- PITCHES -----
Refer to table (pg. 34) of the YM2149 Application Manual.
*/

#define NOTE_PAUSE 0

#define A3 0x1FC
#define A4 0x0FE
#define A5 0X07F
#define A6 0x040

#define B4 0x0E2
#define B5 0x071

#define C3 0x357
#define C5 0x0D6
#define C6 0x06B

#define D5 0x0BE
#define D6 0x05F

#define E3 0x2A7
#define E5 0x0AA
#define E6 0x055

#define F5 0x0A0
#define F6 0x050

#define G1 0x8EB
#define G2 0x475
#define G3 0x23B
#define G4 0x11D
#define G4_SHARP 0x10D
#define G5 0x08F
#define G6 0x047

/*----- NOTE TIMING -----*/
#define FULL_NOTE 120
#define HALF_NOTE 60
#define QUARTER_NOTE 30
#define EIGHTH_NOTE 15

UINT8 read_psg(UINT8 reg);
void write_psg(UINT8 reg, UINT8 val);
void set_tone(UINT8 channel, UINT16 tuning);
void set_volume(UINT8 channel, UINT8 volume);
void set_noise(UINT16 tuning);
void set_envelope(UINT8 shape, UINT16 sustain);
void enable_channel(UINT8 channel, UINT8 tone_on, UINT8 noise_on);
void stop_sound();

#endif