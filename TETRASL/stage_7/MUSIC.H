#ifndef MUSIC_H
#define MUSIC_H

#include "psg.h"

typedef struct
{
    int note;
    int duration;
} Note;

/*----- MUSIC: Tetris Theme A -----
Reference: https://onlinesequencer.net/25593
Details: - Stores each pitch read from the online sequencer.
*/
Note tetris_melody[] = {
    {E6, HALF_NOTE},
    {E5, HALF_NOTE},
    {C6, HALF_NOTE},
    {D6, HALF_NOTE},
    {E6, FULL_NOTE},
    {D6, HALF_NOTE},
    {C6, EIGHTH_NOTE},
    {B5, EIGHTH_NOTE},
    {A5, HALF_NOTE},
    {A5, HALF_NOTE},
    {C6, FULL_NOTE},
    {E6, HALF_NOTE},
    {D6, HALF_NOTE},
    {C6, HALF_NOTE},
    {B5, HALF_NOTE},
    {B5, QUARTER_NOTE},
    {B5, QUARTER_NOTE},
    {C6, QUARTER_NOTE},
    {D6, HALF_NOTE},
    {E6, FULL_NOTE},
    {C6, FULL_NOTE},
    {A5, FULL_NOTE},
    {A5, HALF_NOTE}};

void start_music();
void update_music(UINT32 time_elapsed);

#endif