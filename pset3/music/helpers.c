// Helper functions for music

#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "helpers.h"

#define A4 440


// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int numerator = atoi(strtok(fraction, "/"));
    int denominator = atoi(strtok(NULL, "/"));
    int multiplier = 8 / denominator;
    return numerator * multiplier;
}

/*
 * calculate the difference between the note given and the semitones
 * between it an A note
 */
float distance_from_a(char note)
{
    switch (note)
    {
        case 65: // A
            return 0.0;
        case 66: // B
            return 2.0;
        case 67: // C
            return -9.0;
        case 68: // D
            return -7.0;
        case 69: // E
            return -5.0;
        case 70: // F
            return -4.0;
        case 71: // G
            return -2.0;
    }
    // return -127 (error) if we don't get anything
    return -127.0;
}

/*
 * Calculates frequency (in Hz) of a note
 * The frequency, f, of some note is 2n/12 × 440,
 * where n is the number of semitones from that note to A4
 *
 * each note's frequency is doubled (or halved) for each successive
 * octave. e.g. A4 (440) is double the freq of A3 (220)
 */
int frequency(string note)
{
    // A4 is our base note, so return it if that's what we get
    if (strcmp(note, "A4") == 0)
    {
        return A4;
    }
    else
    {
        int letter;
        int number;
        bool sharp = false;
        bool flat = false;
        float basefreq;
        float freq;

        // split the string into letter (note) and number (octave)
        // check for a '#' to test for sharpness
        for (int z = 0; z < strlen(note); z++)
        {
            if (note[z] >= 65 && note[z] <= 71)
            {
                letter = note[z];
            }
            // note is sharp, so set our bool to true
            else if (note[z] == 35)
            {
                sharp = true;
            }
            // ditto flat
            else if (note[z] == 98)
            {
                flat = true;
            }
            else
            {
                number = atoi(&note[z]);
            }
        }

        // set the base frequency, in relation to A4 as if our note is also
        // in the 4th octave

        // sharp notes are one more semitone away from A
        if (sharp)
        {
            basefreq = pow(2.0, (distance_from_a(letter) + 1.0) / 12.0) * A4;
        }
        else if (flat)
        {
            basefreq = pow(2.0, (distance_from_a(letter) - 1.0) / 12.0) * A4;
        }
        else
        {
            basefreq = pow(2.0, distance_from_a(letter) / 12.0) * A4;
        }

        // half or double the base frequency for each octave
        // depending on whether the octave is > or < 4
        if (number < 4)
        {
            freq = basefreq / (2 * (abs(4 - number)));
        }
        else if (number > 4)
        {
            freq = basefreq * (2 * (number - 4));
        }
        else
        {
            freq = basefreq;
        }
        return round(freq);
    }
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    // check if the string is blank (only a newline)
    if (strcmp(s, "") == 0)
    {
        return true;
    }
    return false;
}