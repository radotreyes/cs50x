#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main( int argc, char* argv[]) {
    /**
     * Vigenere's Cipher
     * Retrieves a plain word and keyword, then returns an encrypted word with characters of the form:
     * encrypted_i = ( plain_i + key_j ) % 26
     *
     * (mod 26 makes sure that A is stored as 0, B as 1, etc.)
     *
     * @param   { char* }   keyword     An encryption key consisting only of alphabetical characters.
     */
    // check for arguments
    if( argc != 2 ) return 1;

    // generate the cipher's modifier from the user input
    char* key = argv[1];
    int keylen = strlen( key );
    int k[keylen];
    for( int ch = 0; ch < keylen; ch++ ) {
        if( !isalpha( key[ch] ) ) {
            return 1;
        }
        k[ch] = tolower( key[ch] ) - 'a';
    }

    // get a plain word from the user and store it
    char* plain = get_string( "plaintext: " );

    // convert the plain word into an array of ints between 0 and 25, representing a to z
    int len = strlen( plain );
    int p[len];
    for( int i = 0; i < len; i++ ) {
        p[i] = tolower( plain[i] ) - 'a';
    }

    // perform vigenere's cipher as detailed above
    int c[len]; // "0-25" representation of the encoded word
    char cipher[len]; // string containing actual ASCII of encoded word
    for( int i = 0, j = 0; i < len; i++ ) {
        if( isalpha( plain[i] ) ) {
            int ascii;
            if( islower( plain[i] ) ) {
                ascii = 'a'; // push lowercase letter if the plain char was originally lowercase
            }
            else {
                ascii = 'A'; // push lowercase letter if the plain char was originally lowercase
            }
            c[i] = ( p[i] + k[j] ) % 26;
            cipher[i] = c[i] + ascii;

            if( key[j + 1] == '\0' ) {
                j = 0;
            }
            else {
                j++;
            }
        }
        else {
            cipher[i] = plain[i]; // if plain was not alphanumeric, just push the character
        }

    }

    printf( "ciphertext: %s\n", cipher );
    return 0;
}