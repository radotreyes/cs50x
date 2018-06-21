#define _XOPEN_SOURCE
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main( int argc, char* argv[]) {
    if( argc != 2 ) {
        printf( "crack only takes one argument!\n" );
        return 1;
    }

    // separate the salt from the encrypted password
    char salt[3];
    for( int saltIterator = 0; saltIterator < 2; saltIterator++ ) {
        salt[saltIterator] = argv[1][saltIterator];
    }
    salt[2] = '\0'; // salt is a string, need to null-terminate

    // make a string of all possible characters
    char chars[53]; // store all lowercase alphanumeric characters
    char currentLetter = 'A';
    for( int cur = 0; cur < 52; cur++ ) {
        if( currentLetter == '[' ) currentLetter = 'a';
        chars[cur] = currentLetter;
        currentLetter++;
    }
    chars[52] = '\0'; // terminate string

    char guess[6]; // the passwords being tested can be no longer than five characters
    char* decrypted = "A"; // the return value of crypt is always 13 chars

    // guess with one character
    printf( "guessing...\n" );
    for( int a = 0; a < 52; a++ ) {
        guess[0] = chars[a];
        guess[1] = '\0';
        decrypted = crypt( guess, salt );
        if( strcmp( decrypted, argv[1] ) == 0 ) {
            printf( "%s\n", guess );
            return 0;
        }
    }

    // guess with two characters
    printf( "guessing...\n" );
    for( int b = 0; b < 52; b++ ) {
        guess[0] = chars[b];
        for( int c = 0; c < 52; c++ ) {
            guess[1] = chars[c];
            guess[2] = '\0';
            decrypted = crypt( guess, salt );
            if( strcmp( decrypted, argv[1] ) == 0 ) {
                printf( "%s\n", guess );
                return 0;
            }
        }
    }

    // guess with three characters
    printf( "guessing...\n" );
    for( int d = 0; d < 52; d++ ) {
        guess[0] = chars[d];
        for( int e = 0; e < 52; e++ ) {
            guess[1] = chars[e];
            for( int f = 0; f < 52; f++ ) {
                guess[2] = chars[f];
                guess[3] = '\0';
                decrypted = crypt( guess, salt );
                if( decrypted == argv[1] ) break;
            }
        }
    }

    // guess with four characters
    printf( "guessing...\n" );
    for( int g = 0; g < 52; g++ ) {
        guess[0] = chars[g];
        for( int h = 0; h < 52; h++ ) {
            guess[1] = chars[h];
            for( int i = 0; i < 52; i++ ) {
                guess[2] = chars[i];
                for( int j = 0; j < 52; j++ ) {
                    guess[3] = chars[j];
                    guess[4] = '\0';
                    decrypted = crypt( guess, salt );
                    if( strcmp( decrypted, argv[1] ) == 0 ) {
                        printf( "%s\n", guess );
                        return 0;
                    }
                }
            }
        }
    }

    // guess with five characters
    printf( "guessing...\n" );
    for( int k = 0; k < 52; k++ ) {
        guess[0] = chars[k];
        for( int l = 0; l < 52; l++ ) {
            guess[1] = chars[l];
            for( int m = 0; m < 52; m++ ) {
                guess[2] = chars[m];
                for( int n = 0; n < 52; n++ ) {
                    guess[3] = chars[n];
                    for( int o = 0; o < 52; o++ ) {
                        guess[4] = chars[o];
                        guess[5] = '\0';
                        decrypted = crypt( guess, salt );
                        if( strcmp( decrypted, argv[1] ) == 0 ) {
                            printf( "%s\n", guess );
                            return 0;
                        }
                    }
                }
            }
        }
    }
}
