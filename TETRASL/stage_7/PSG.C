/**
 * @file PSG.C
 * @brief contains PSG (Programmable Sound Generator) library.
 *        See the YM2149 manual for more details.
 * @author Mack Bautista
 */

#include "psg.h"
#include <stdio.h>

/*
----- FUNCTION: read_psg -----
Purpose:
    - Reads the value from YM2149 register.
    - Consult with the YM2149 Application Manual as register address could differ with other
      sound chips.

Details:
    - The function interacts directly with the hardware registers of the PSG to retrieve the current value stored in the specified register.
    - It includes boundary checks to ensure the register index is within the valid range (0-15).
    - Preserves the previous supervisor state while accessing the PSG registers.

Parameters:
    - int reg:        The index of the PSG register to read from (valid range: 0-15).

Return Value:
    - UINT8:          The value stored in the specified PSG register. Returns 0 if the register index is invalid.

Limitations:
    - Assumes the hardware registers are accessible at memory addresses 0xFF8800 and 0xFF8802.
    - If the register index is out of range, the function returns 0 without attempting to read from the hardware.
*/
UINT8 read_psg(UINT8 reg)
{
    volatile UINT8 *PSG_reg_read = PSG_REG_SELECT_ADDRESS;
    UINT32 old_ssp;
    UINT8 value = 0;

    if (reg < 0 || reg > 15)
    {
        return 0;
    }

    old_ssp = Super(0);
    value = *PSG_reg_read;
    Super(old_ssp);

    return value;
}

/*
----- FUNCTION: write_psg -----
Purpose:
    - Reads the value from YM2149 register.
    - Consult with the YM2149 Application Manual as register address could differ with other
      sound chips.
Details:
    - The function interacts directly with the hardware registers of the PSG.
    - It ensures that the specified register is updated with the provided value while preserving the previous supervisor state.
    - The function includes boundary checks to ensure the register index is within the valid range (0-15).

Parameters:
    - int reg:        The index of the PSG register to write to (valid range: 0-15).
    - UINT8 val:      The value to write to the specified PSG register.

Limitations:
    - Assumes the hardware registers are accessible at memory addresses 0xFF8800 and 0xFF8802.
    - Does not provide feedback if the register index is out of range; invalid indices are ignored.
*/
void write_psg(UINT8 reg, UINT8 val)
{
    volatile UINT8 *PSG_reg_select = PSG_REG_SELECT_ADDRESS;
    volatile UINT8 *PSG_reg_write = PSG_REG_WRITE_ADDRESS;
    UINT32 old_ssp;

    if (reg < 0 || reg > 15)
    {
        return;
    }

    old_ssp = Super(0);
    *PSG_reg_select = reg;
    *PSG_reg_write = val;
    Super(old_ssp);
}

/*
----- FUNCTION: set_tone -----
Purpose:
    - Configures the tone frequency for a specified PSG channel by loading the coarse and fine tuning registers.

Details:
    - The function calculates and writes the 12-bit tuning value into the tone registers of the specified channel.
    - It ensures the channel is valid (0 for A, 1 for B, 2 for C) and restricts the tuning value to the 12-bit range (0-4095).
    - The tone registers are divided into fine and coarse components:
        - Fine: Lower 8 bits of the tuning value.
        - Coarse: Upper 4 bits of the tuning value.

Parameters:
    - int channel:    The PSG channel to configure (0 = A, 1 = B, 2 = C).
    - int tuning:     The 12-bit tuning value (valid range: 0-4095).

Limitations:
    - Assumes the hardware registers are accessible at memory addresses 0xFF8800 and 0xFF8802.
    - If the channel or tuning value is out of range, the function does nothing.
*/
void set_tone(UINT8 channel, UINT16 tuning)
{
    int fine_tuning, coarse_tuning;
    if (channel < 0 || channel > 2 || tuning < 0 || tuning > 0xFFF)
    {
        return;
    }

    fine_tuning = tuning & 0xFF;
    coarse_tuning = tuning >> 8;

    write_psg(channel << 1, (UINT8)fine_tuning);
    write_psg((channel << 1) + 1, (UINT8)coarse_tuning);
}

/*
----- FUNCTION: set_volume -----
Purpose:
    - Configures the volume level for the YM2149 sound chip.
    - Consult with the YM2149 Application Manual as register address could differ with other
      sound chips.

Details:
    - The function writes the provided volume level to the volume register of the specified channel.
    - Ensures the channel is valid (0 for A, 1 for B, 2 for C) and restricts the volume level to the valid range (0-15).
    - Volume levels range from 0 (silent) to 15 (maximum volume).

Parameters:
    - int channel:    The PSG channel to configure (0 = A, 1 = B, 2 = C).
    - int volume:     The volume level (valid range: 0-15).

Limitations:
    - Assumes the hardware registers are accessible via the 'write_psg' function.
    - If the channel or volume level is out of range, the function does nothing.
*/
void set_volume(UINT8 channel, UINT8 volume)
{
    if (channel < 0 || channel > 2 || volume < 0 || volume > 0x1F)
    {
        return;
    }

    write_psg(8 + channel, volume);
}

/*
----- FUNCTION: set_noise -----
Purpose:
    - Configures the YM2149 noise generator with the specified tuning.

Details:
    - This function writes the tuning value to the noise register of the PSG.
    - The tuning value determines the frequency of the noise output.

Parameters:
    - int tuning: The tuning value for the noise generator (valid range: 0x00 - 0x1F).

Limitations:
    - Assumes the tuning value is within the valid range.
*/
void set_noise(UINT16 tuning)
{
    if (tuning < 0x00 || tuning > 0x1F)
    {
        return;
    }
    write_psg(NOISE_FREQ, tuning);
}

/*
----- FUNCTION: set_envelope -----
Purpose:
    - Configures the YM2149 envelope generator with the specified shape and sustain value.
    - Consult with the YM2149 Application Manual as register address could differ with other
      sound chips.

Details:
    - This function sets the envelope shape and sustain time for amplitude modulation.
    - It writes the shape to the envelope control register and the 16-bit sustain value
      to the coarse and fine registers of the envelope generator.

Parameters:
    - int shape:              The envelope shape (valid range: 0-15).
    - unsigned int sustain:   The 16-bit sustain value (valid range: 0-65535).

Limitations:
    - Assumes the shape value is within the valid range. If the value exceeds
      the valid range, it will be masked to the lower 4 bits (0-15).
    - Assumes the sustain value is within the valid range. If the value exceeds
      the valid range, only the lower 16 bits will be used.
*/
void set_envelope(UINT8 shape, UINT16 sustain)
{
    UINT16 coarse_tuning, fine_tuning;

    coarse_tuning = (sustain >> 8);
    fine_tuning = sustain & 0xFF;

    write_psg(ENV_FREQ_FINE, (UINT8)fine_tuning);
    write_psg(ENV_FREQ_COARSE, (UINT8)coarse_tuning);
    write_psg(ENV_SHAPE, shape);
}

/*
----- FUNCTION: enable_channel -----
Purpose:
    - Configures the tone and noise signals for a specified YM2149 channel.
    - Consult with the YM2149 Application Manual as register address could differ with other
      sound chips.

Details:
    - The function modifies the PSG mixer control register to enable or disable tone and noise signals for the given channel.
    - Ensures the channel is valid (0 for A, 1 for B, 2 for C) and the control flags are either 0 (off) or 1 (on).
    - The mixer control register determines which signals are active for each channel.

Parameters:
    - int channel:    The PSG channel to configure (0 = A, 1 = B, 2 = C).
    - int tone_on:    Enables (1) or disables (0) the tone signal for the channel.
    - int noise_on:   Enables (1) or disables (0) the noise signal for the channel.

Limitations:
    - Assumes the hardware registers are accessible via the 'write_psg' and 'read_psg' functions.
    - If the channel or control flags are out of range, the function does nothing.
*/
void enable_channel(UINT8 channel, UINT8 tone_on, UINT8 noise_on)
{
    UINT8 tone_bit, noise_bit, mixer_value;

    if (channel < 0 || channel > 2 || tone_on < 0 || tone_on > 1 || noise_on < 0 || noise_on > 1)
    {
        return;
    }

    tone_bit = 1 << channel;
    noise_bit = 1 << (channel + 3);
    mixer_value = read_psg(MIXER);

    if (tone_on)
    {
        mixer_value &= ~tone_bit;
    }
    else
    {
        mixer_value |= tone_bit;
    }

    if (noise_on)
    {
        mixer_value &= ~noise_bit;
    }
    else
    {
        mixer_value |= noise_bit;
    }

    write_psg(MIXER, mixer_value);
}

/*
----- FUNCTION: stop_sound -----
Purpose:
    - Silences all sound output from the PSG by disabling tone and noise signals and setting all volumes to zero.

Details:
    - The function clears all tone and noise signals in the mixer control register.
    - It also sets the volume of all channels (A, B, C) to 0.

Limitations:
    - Assumes the hardware registers are accessible via the 'write_psg' function.
*/
void stop_sound()
{
    set_tone(CHANNEL_A, 0);
    set_tone(CHANNEL_B, 0);
    set_tone(CHANNEL_C, 0);
    write_psg(NOISE_FREQ, 0);
    write_psg(MIXER, 0xFF);
    write_psg(A_LEVEL, 0);
    write_psg(B_LEVEL, 0);
    write_psg(C_LEVEL, 0);
    set_envelope(0, 0);
}