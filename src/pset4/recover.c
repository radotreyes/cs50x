#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

bool isjpeg( uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4 ) {
    return (
        b1 == 255 &&
        b2 == 216 &&
        b3 == 255 &&
        b4 >= 224
    );
}

int ones( int num ) {
    return num % 10;
}
int tens( int num ) {
    return ( num - ones( num ) ) / 10 % 10;
}
int hundreds( int num ) {
    return ( num - ( tens( num ) * 10 ) - ones( num ) ) / 100;
}
char* generatefilename( int filenum ) {
    char* outf = malloc( sizeof( "aaa.jpg" ) * sizeof( char ) );
    sprintf(
        outf,
        "%d%d%d.jpg",
        hundreds( filenum ),
        tens( filenum ),
        ones( filenum )
    );

    return outf;
}

int main( int argc, char* argv[] ) {
    // ensure proper usage
    if ( argc != 2 ) {
        fprintf( stderr, "Usage: ./recover rawfile\n" );
        return 1;
    }

    // remember and open read file
    char* infile = argv[1];
    FILE* inptr = fopen( infile, "r" );
    if( inptr == NULL ) {
        fprintf( stderr, "Could not open %s.\n", infile );
        return 2;
    }

    // output files in ascending number order, starting from 0
    // init at -1; the first time we see a jpeg this gets incremented
    int filenum = -1;

    // create a new write file for every JPEG we see, starting with "000"
    char* outfile = NULL;

    // initialize the write file pointer
    FILE* outptr = NULL;

    // declare buffer of FAT block size (FAT-512)
    uint8_t* b = malloc( 512 * sizeof( uint8_t ) );

    while( fread( b, 512 * sizeof( uint8_t ), 1, inptr ) && !feof( inptr ) ) {
        // look for a JPEG signature
        if( isjpeg( b[0], b[1], b[2], b[3] ) ) {
            // save and close the current write file if it exists
            if( outptr != NULL ) fclose( outptr );
            filenum++;
            outfile = generatefilename( filenum );

            // open a new write file
            // set the current write file to the new one we just opened
            outptr = fopen( outfile, "w+" );
            if( outptr == NULL ) {
                fclose( inptr );
                fprintf( stderr, "Could not create %s.\n", outfile );
                return 3;
            }
        }
        // write the contents of the input buffer
        if( outptr != NULL ) fwrite( b, 512 * sizeof( *b ), 1, outptr );
    }

    // close infile
    fclose( inptr );

    // close outfile
    fclose( outptr );

    // success
    return 0;
}
