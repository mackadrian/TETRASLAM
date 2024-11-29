#include "music.h"
#include <stdio.h.>

/*GLOBAL VARIABLES*/
UINT32 melody_timing;
UINT16 melody_tracking;

void start_music()
{
    melody_timing = tetris_melody[melody_tracking].duration;
    set_tone(CHANNEL_A, tetris_melody[melody_tracking].note);
    set_envelope(0x1000, 3);
    enable_channel(CHANNEL_A, TONE_ON, NOISE_OFF);
    set_volume(CHANNEL_A, 0x10);
    melody_tracking++;
}
