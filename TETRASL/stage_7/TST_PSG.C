#include "psg.h"
#include <osbind.h>
#include <stdio.h>

void delay(int ms);
void play_note(int channel, int tuning, int volume, int duration_ms);

int main()
{
    int i;
    /* Test set_tone function */
    printf("TEST 1: SETTING ALL FUNCTIONS...\n");
    printf("Testing set_tone...\n");
    printf("\n");
    Cnecin();
    set_tone(0, 1000);
    Cnecin();
    set_tone(1, 2000);
    Cnecin();
    set_tone(2, 3000);

    printf("Testing set_volume...\n");
    Cnecin();
    set_volume(0, 10);
    Cnecin();
    set_volume(1, 5);
    Cnecin();
    set_volume(2, 0);

    printf("Testing enable_channel...\n");
    Cnecin();
    enable_channel(0, 1, 1);
    Cnecin();
    enable_channel(1, 1, 0);
    Cnecin();
    enable_channel(2, 0, 1);

    printf("Testing stop_sound...\n");
    Cnecin();
    stop_sound();

    printf("All tests completed.\n");
    printf("\n");

    printf("TEST 2: SOUND TESTS...\n");
    printf("Starting PSG test...\n");

    play_note(0, A5, 10, 500);
    play_note(0, B5, 10, 500);
    play_note(0, C5, 10, 500);
    play_note(0, D5, 10, 500);
    play_note(0, G4_SHARP, 10, 500);
    stop_sound();
    printf("PSG test complete.\n");
    return 0;
}

void delay(int ms)
{
    /* Simple delay loop for timing; adjust based on the clock speed */
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
