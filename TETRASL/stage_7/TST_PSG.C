#include "psg.h"
#include "effects.h"
#include "music.h"
#include <osbind.h>
#include <stdio.h>

#define MELODY_LENGTH (sizeof(tetris_melody) / sizeof(tetris_melody[0]))

/*FUNCTION DECLARATIONS*/
void delay(int ms);
void play_note(int channel, int tuning, int volume, int duration_ms);
void test_notes();
void test_effects();
void test_music();
UINT32 get_time();

int main()
{
    test_music();
    /*test_notes();
    test_effects();*/

    return 0;
}

void delay(int ms)
{
    volatile int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 1000; j++)
        {
        }
}

void play_note(int channel, int tuning, int volume, int duration_ms)
{
    set_tone(channel, tuning);
    set_volume(channel, volume);
    enable_channel(channel, 1, 0);
    delay(duration_ms);
    set_volume(channel, 0);
}

/*
----- FUNCTION: test_notes -----
Purpose:
    - Plays a sequence of musical notes on Channel A repeatedly until the spacebar is pressed.

Details:
    - This function tests the ability to generate musical notes with a consistent rhythm.
    - It loops through a sequence of notes (A5, B5, C5, D5, G5) and plays each note with a
      specified duration and volume.
    - The function listens for a spacebar keypress using Cnecin(), which stops the test.

Limitations:
    - Assumes that Cnecin() can detect spacebar presses correctly.
    - May exhibit delay depending on the implementation of the delay function.
*/
void test_notes()
{
    int pitches[] = {
        A3, A4, A5,
        B4, B5,
        C3, C5, C6,
        D5, D6,
        E3, E5, E6,
        G1, G2, G3, G4, G4_SHARP, G5};
    int i;
    char key;

    printf("\n");
    printf("TESTING NOTES IN CHANNEL A...\n");
    printf("Press the spacebar to stop the test. Press other keys to continue...\n");

    while (1)
    {
        key = Cnecin();

        if (key == ' ')
        {
            printf("Spacebar pressed, stopping the sound test.\n");
            stop_sound();
            break;
        }

        for (i = 0; i < 19; i++)
        {
            play_note(CHANNEL_A, pitches[i], 10, 100);
        }
        printf("All pitches have been played. Awaiting input...\n");
    }
}

/*
----- FUNCTION: test_effects -----
Purpose:
    - Tests the drop sound effect repeatedly until the spacebar is pressed.

Details:
    - This function is designed to validate the sound effect associated with a "drop" action.
    - It plays the drop sound in a continuous loop, allowing the user to evaluate the sound effect.
    - The function listens for a spacebar keypress using Cnecin(), which stops the test.

Limitations:
    - Assumes that Cnecin() can detect spacebar presses correctly.
    - May exhibit delay depending on the implementation of the delay function.
*/
void test_effects()
{
    char key;
    printf("\n");
    printf("TESTING DROP SOUND EFFECT...\n");
    printf("Press the spacebar to stop the test. Press other keys to continue...\n");

    while (1)
    {
        key = Cnecin();

        if (key == ' ')
        {
            printf("Spacebar pressed, stopping the sound test.\n");
            break;
        }

        printf("Loading drop sound...\n");
        delay(300);
        play_drop_sound();

        printf("Loading boundary collision sound...\n");
        delay(300);
        play_bounds_collision_sound();
    }

    stop_sound();
}

/*
----- FUNCTION: test_music -----
Purpose:
    - Tests the Tetris theme music playback until the spacebar is pressed.

Details:
    - This function simulates the playback of the Tetris theme melody.
    - The melody is played by calling `start_music` to initialize the first note and `update_music` to update and transition between notes based on the elapsed time.
    - The function listens for a spacebar keypress using `Cnecin()`, which stops the playback of the theme by calling `stop_sound()`.

Limitations:
    - Assumes that `Cnecin()` correctly detects the spacebar press to stop the melody.
    - The time is incremented manually (using a simple counter) instead of relying on a system timer or clock.
*/
void test_music()
{
    UINT32 time_then, time_now, time_elapsed;
    UINT32 melody_time_elapsed = 0;
    char key = 0;

    printf("Playing Tetris Theme...\n");

    start_music();
    time_then = get_time();

    while (key != ' ')
    {
        if (Cconis())
        {
            key = Cnecin();
            if (key == ' ')
            {
                printf("Spacebar pressed, stopping the Tetris theme.\n");
                stop_sound();
                return;
            }
        }

        time_now = get_time();

        time_elapsed = time_now - time_then;

        if (time_elapsed > 1)
        {
            time_then = time_now;
            melody_time_elapsed++;
            update_music(&melody_time_elapsed);
        }
    }

    stop_sound();
    printf("Tetris Theme completed.\n");
}

/*
----- FUNCTION: get_time -----
P. Pospisil, "get_time function," lab material, COMP2659 Computing Machinery II , Mount Royal University, Nov. 2024.
Author: Paul Pospisil

Purpose:
    - Retrieves the current time from the CPU clock through supervisor access.

Details:
    - This function accesses the system timer, which is automatically incremented 70 times per second, and retrieves
      the current value of the timer.

Return:
    - UINT32:     The current system time.

Limitations:
    - Supervisor mode must be exited after usage.
*/
UINT32 get_time()
{
    UINT32 time_now;
    UINT32 old_ssp;
    UINT32 *timer = (UINT32 *)0x462; /*address of a long word that is auto incremented 70 times per second */

    old_ssp = Super(0); /* enter privileged mode */
    time_now = *timer;
    Super(old_ssp); /* exit privileged mode */

    return time_now;
}