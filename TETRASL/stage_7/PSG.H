#ifndef PSG_H
#define PSG_H

#include "types.h"
#include <osbind.h>

/*-----Pitches-----
Refer to table (pg. 34) of the YM2149 Application Manual.
*/
#define A3 0x1FC
#define A4 0x0FE
#define A5 0X07F

#define B4 0x0E2
#define B5 0x071

#define C5 0x0D6
#define C6 0x06B

#define D5 0x0BE
#define D6 0x05F

#define E3 0x2A7
#define E5 0x0AA
#define E6 0x055

#define G2 0x475
#define G4_SHARP 0x10D

UINT8 read_psg(int reg);
void write_psg(int reg, UINT8 val);
void set_tone(int channel, int tuning);
void set_volume(int channel, int volume);
void enable_channel(int channel, int tone_on, int noise_on);
void stop_sound();

#endif