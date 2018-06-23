// Helper functions for music

#include <cs50.h>
#include "helpers.h"
#include <math.h>
#include <string.h>

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    // arguments will only be passed in the above format X/Y so
    // we can manipulate the string addresses without errors
    int numerator = (fraction[0] - '0');
    int denominator = (fraction[2] - '0');

    // normalize the fraction to be of x'/8
    int operand; // operand to multiply or divide denominator by
    if(denominator > 8) {
    // if the denominator is larger than 8, we need to multiply the numerator by
    // the denominator's count of orders of magnitude larger than 8
        operand = denominator / 8; // gets 2 for 16, 4 for 32, etc.
        denominator /= operand; // normalizes the denominator to 8
        numerator /= operand; // 16/16 -> 8/8. 16/32 -> 4/8, etc.
    }
    else if(denominator <= 8) {
    // if the denominator is less than 8, we need to divide the numerator by
    // the denominator's count of orders of magnitude smaller than 8
        operand = 8 / denominator; // gets 1 for 8, 2 for 4, 4 for 2, 8 for 1
        denominator *= operand; // normalizes the denominator to 8
        numerator *= operand; // 1/4 -> 2/8, 1/2 -> 4/8, etc.
    }

    return numerator; // 1/4 -> 2/8 -> returns 2, 1/2 -> 4/8 -> returns 4, etc.
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    /* parse the note input */
    char key = note[0];
    int accidental = note[1] == '#'|| (note[1] == 'b') || 0;
    if(note[1] == 'b') accidental *= -1;
    int octave;
    if(accidental) {
        octave = note[2] - '0';
    }
    else {
        octave = note[1] - '0';
    }

    /* determine the position of the input note relative to A */
    // indexed map of relative position from A, shifted down by 1
    // note that after A4 and B4 comes C5, have to treat A & B mathematically as if they were shifted up by one octave
    char scale[11] = {'\0', 'B', 'C', '\0', 'D', '\0', 'E', 'F', '\0', 'G', '\0'};
    int n = 0; // # of semitones away from A
    for(int i = 0; i < 10; i++) {
        if(key == scale[i]) {
            if(octave <= 4 && key != 'A' && key != 'B') { // apply the adjustment on line 53
                i = -1 * (11 - i) - 1; // if lower octave, calculate relative position in descending scale
            }
            i += 1;
            n += i;
            break;
        }
    }
    n += accidental; // factor in accidentals as +/- one semitone
    if(octave > 4 && key != 'A' && key != 'B') octave -= 1; // apply the adjustment on line 53

    /* frequency is defined as f = 2^(n/12) * 440; let 2^(n/12) be denoted as k */
    double oexp = pow(2, octave - 4); // gets 1 for 0, 2 for 1, 4 for 2, etc.
    double k = pow(2, (double) n / (double) 12);
    return round(k * oexp * 440);
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    // rests are \r, \n, \r\n
    return !strcmp(s, "\n") || !strcmp(s, "\r") || !strcmp(s, "\r\n") || !strcmp(s, "");
}
