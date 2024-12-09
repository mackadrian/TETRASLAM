#include "music.h"
#include <stdio.h>

/*GLOBAL VARIABLES*/
UINT32 melody_timing;
UINT16 current_note;

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
    - Increments 'current_note' to advance to the next note in the melody sequence.
    - Adjusts the 'melody_timing' variable to reflect the duration of the current note, ensuring proper timing.

Limitations:
    - The function assumes that the 'tetris_melody' array is properly defined and terminated.
    - Relies on external functions ('set_tone', 'set_envelope', 'enable_channel', and 'set_volume') for sound generation.
    - Does not handle the end of the melody sequence explicitly (e.g., looping or stopping).
*/
void start_music()
{
    current_note = 0;
    melody_timing = tetris_melody[current_note].duration;

    set_tone(CHANNEL_A, tetris_melody[current_note].note);
    set_volume(CHANNEL_A, 0x08);
    enable_channel(CHANNEL_A, TONE_ON, NOISE_OFF);
    set_envelope(0x03, 0x1000);
}

/*
----- FUNCTION: update_music -----
Purpose:
    - Updates the current note of the melody based on the elapsed time, ensuring the appropriate
      note is played or paused.
    - Advances to the next note in the sequence if the duration of the current note has elapsed.

Details:
    - The function checks if the elapsed time ('melody_time_elapsed') exceeds the duration of the
      current note ('melody_timing'). If true, it transitions to the next note.
    - If the note is not a pause ('NOTE_PAUSE'), the function sets the tone for 'CHANNEL_A' and
      enables the audio channel. If it is a pause, the tone is disabled.
    - If the end of the melody is reached, the melody loops back to the beginning.

Parameters:
    - UINT32 *melody_time_elapsed: A pointer to the elapsed time counter, representing the total
      time passed since the start of the current melody.

Global Variables:
    - tetris_melody: An array of 'Note' structures containing the melody's notes and durations.
    - current_note: An index tracking the current note in the melody.
    - melody_timing: The duration of the current note, updated when transitioning to a new note.

Limitations:
    - Assumes that 'melody_timing' and 'current_note' are initialized correctly before calling the function.
    - The function does not handle scenarios where 'melody_time_elapsed' overflows.
    - It relies on the global 'tetris_melody' array being appropriately sized and defined.

*/
void update_music(UINT32 *melody_time_elapsed)
{

    if (*(melody_time_elapsed) > melody_timing)
    {
        melody_timing = tetris_melody[current_note].duration;

        if (tetris_melody[current_note].note != NOTE_PAUSE)
        {
            set_tone(CHANNEL_A, tetris_melody[current_note].note);
            enable_channel(CHANNEL_A, TONE_ON, NOISE_OFF);
        }
        else
        {
            enable_channel(CHANNEL_A, TONE_OFF, NOISE_OFF);
        }

        current_note++;
        if (current_note > NUM_MELODY_NOTES)
        {
            current_note = 0;
        }
    }
}
