#include "music.h"
#include <stdio.h.>

/*GLOBAL VARIABLES*/
UINT32 melody_timing;
UINT16 melody_tracking;

/*
----- FUNCTION: start_music -----
Purpose:
    - Starts the Tetris melody sequence.

Details:
    - This function handles the playback of the predefined Tetris melody by iterating through the 'tetris_melody' array.
    - For each note in the melody:
        - Sets the tone and envelope for the specified channel.
        - Enables the channel for tone playback without noise.
        - Configures the volume for the channel.
    - Increments 'melody_tracking' to advance to the next note in the melody sequence.
    - Adjusts the 'melody_timing' variable to reflect the duration of the current note, ensuring proper timing.

Limitations:
    - The function assumes that the 'tetris_melody' array is properly defined and terminated.
    - Relies on external functions ('set_tone', 'set_envelope', 'enable_channel', and 'set_volume') for sound generation.
    - Does not handle the end of the melody sequence explicitly (e.g., looping or stopping).
*/
void start_music()
{
    melody_tracking = 0;
    melody_timing = tetris_melody[melody_tracking].duration;

    set_tone(CHANNEL_A, tetris_melody[melody_tracking].note);
    set_envelope(0x03, 0x1000);
    enable_channel(CHANNEL_A, TONE_ON, NOISE_OFF);
    set_volume(CHANNEL_A, 0x10);
}

void update_music(UINT32 time_elapsed)
{
    if (time_elapsed >= melody_timing)
    {
        time_elapsed -= melody_timing;

        melody_tracking++;
        if (melody_tracking >= NUM_MELODY_NOTES)
        {
            melody_tracking = 0;
        }

        set_tone(CHANNEL_A, tetris_melody[melody_tracking].note);
        set_envelope(0x03, 0x1000);
        enable_channel(CHANNEL_A, TONE_ON, NOISE_OFF);
        set_volume(CHANNEL_A, 0x10);

        melody_timing = tetris_melody[melody_tracking].duration;
    }
}
