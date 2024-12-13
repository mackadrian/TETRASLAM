#include "effects.h"

/*
----- FUNCTION: play_drop_sound -----
Purpose:
    - Plays the "drop" sound effect using Channel C.
    - Configures tone, noise, volume, and envelope parameters to produce the effect.

Details:
    - Utilizes the PSG library to set up Channel C for sound effect playback.
    - Designed to exclusively use Channel C, leaving Channels A and B for music.

Limitations:
    - The function assumes Channel C is reserved for sound effects.
*/
void play_drop_sound()
{
    set_tone(CHANNEL_C, G3);
    set_volume(CHANNEL_C, 0x10);
    enable_channel(CHANNEL_C, TONE_ON, NOISE_OFF);
    set_envelope(0x01, 0x00E0);
}

/*
----- FUNCTION: play_bounds_collision_sound -----
Purpose:
    - Plays the "boundary collision" sound effect using Channel C.
    - Indicates when the active piece collides with the playing field's boundary.

Details:
    - Utilizes the PSG library to configure Channel C for the effect.
    - Produces a distinct, short "beep" sound.

Limitations:
    - Assumes Channel C is reserved for sound effects.
    - The sound duration is tied to the envelope settings and cannot be manually adjusted.
*/
void play_bounds_collision_sound()
{
    set_tone(CHANNEL_C, G4_SHARP);
    set_volume(CHANNEL_C, 0x10);
    enable_channel(CHANNEL_C, TONE_ON, NOISE_OFF);
    set_envelope(0x01, 0x00E0);
}

/*
----- FUNCTION: play_bounds_collision_sound -----
Purpose:
    - Plays the "clear row" sound effect using Channel C.
    - Indicates a row clearance occurs.

Details:
    - Utilizes the PSG library to configure Channel C for the effect.
    - Produces a distinct, short "beep" sound.

Limitations:
    - Assumes Channel C is reserved for sound effects.
    - The sound duration is tied to the envelope settings and cannot be manually adjusted.
*/
void play_clear_row_sound()
{
    set_tone(CHANNEL_C, A3);
    set_volume(CHANNEL_C, 0x10);
    enable_channel(CHANNEL_C, TONE_ON, NOISE_OFF);
    set_envelope(0x01, 0x00E0);
}