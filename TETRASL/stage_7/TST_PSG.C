#include "psg.h"
#include "effects.h"
#include <osbind.h>
#include <stdio.h>

#define MELODY_LENGTH (sizeof(melody) / sizeof(melody[0]))
#define NOTE_DURATION 70

typedef struct
{
    int pitch;
    int duration;
} Note;

Note melody[] = {
    {C5, 70},  /* C5, short note (eighth note) */
    {C5, 70},  /* C5, short note */
    {D5, 140}, /* D5, longer note (quarter note) */
    {E5, 70},  /* E5, short note */
    {C5, 70},  /* C5, short note */
    {F5, 140}, /* F5, longer note */
    {E5, 70},  /* E5, short note */
    {D5, 70},  /* D5, short note */
    {C5, 140}, /* C5, longer note */
    {B4, 70},  /* B4, short note */
    {C5, 140}, /* C5, longer note */
    {A4, 70},  /* A4, short note */
    {B4, 70},  /* B4, short note */
    {A4, 140}, /* A4, longer note */
    {F5, 70},  /* F5, short note */
    {G5, 140}, /* G5, longer note */
    {A4, 70},  /* A4, short note */
    {B4, 70},  /* B4, short note */
    {C5, 280}  /* C5, very long note (half note) */
};

/*FUNCTION DECLARATIONS*/
void delay(int ms);
void play_note(int channel, int tuning, int volume, int duration_ms);
void test_notes();
void test_effects();
void play_tetris_theme();

int main()
{
    play_tetris_theme();
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

void play_tetris_theme()
{
    char key;
    int i;
    unsigned int ticks = 0;

    /* Print the start message */
    printf("Playing Tetris Theme...\n");

    while (1)
    {
        key = Cnecin();
        /* Loop through all notes in the melody */
        for (i = 0; i < MELODY_LENGTH; i++)
        {
            Note current_note = melody[i];

            /* If the note has a valid pitch, play the note */
            if (current_note.pitch > 0)
            {
                play_note(CHANNEL_A, current_note.pitch, 10, current_note.duration);
            }

            /* Start counting ticks for the note duration */
            ticks = 0;
            while (ticks < current_note.duration)
            {
                /* Check if spacebar is pressed to stop the melody */
                if (key == ' ') /* User pressed space */
                {
                    printf("Spacebar pressed, stopping the Tetris theme.\n");
                    stop_sound(); /* Stop playing sound */
                    return;       /* Exit the function */
                }
                ticks++; /* Wait for the duration of the note */
            }
        }
    }
}