#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main( int argc, char* argv[] ) {
    // accept only 2 arguments
    if( argc != 3 ) {
        fprintf( stderr, "Usage: ./whodunit infile outfile\n" );
        return 1;
    }

    // store filename input strings
    char* infile = argv[1];
    char* outfile = argv[2];

    // open read file
    FILE* inptr = fopen( infile, "r" );
    if( inptr == NULL ) {
        fprintf( stderr, "Couldn't open file \"%s\".\n", infile );
        return 2;
    }

    // open write file
    FILE* outptr = fopen( outfile, "w" );
    if( outptr == NULL ) {
        fprintf( stderr, "Couldn't open file \"%s.\"\n", outfile );
        return 3;
    }

    // read write file's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread( &bf, sizeof( BITMAPFILEHEADER ), 1, inptr );

    // read write file's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread( &bi, sizeof( BITMAPINFOHEADER ), 1, inptr );

    // return error if read file isn't an uncompressed BMP-24 4.0
    if(
        bf.bfType != 0x4d42 ||
        bf.bfOffBits != 54 ||
        bi.biSize != 40 ||
        bi.biBitCount != 24 ||
        bi.biCompression != 0
    ) {
        fclose( outptr );
        fclose( inptr );
        fprintf( stderr, "Unsupported file format.\n" );
        return 4;
    }

    // write write file's BITMAPFILEHEADER
    fwrite( &bf, sizeof(BITMAPFILEHEADER), 1, outptr );

    // write write file's BITMAPINFOHEADER
    fwrite( &bi, sizeof(BITMAPINFOHEADER), 1, outptr );

    // // determine padding for scanlines
    // int padding = ( 4 - ( bi.biWidth * sizeof( RGBTRIPLE )) % 4 ) % 4;

    // iterate over read file's scanlines
    for( int i = 0, biHeight = abs( bi.biHeight ); i < biHeight; i++ ) {
        // iterate over pixels in scanline
        for ( int j = 0; j < bi.biWidth; j++ ) {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread( &triple, sizeof( RGBTRIPLE ), 1, inptr );

            // write RGB triple to outfile
            // replace all instances of red with white
            if( triple.rgbtBlue == 255 && triple.rgbtGreen == 255 && triple.rgbtRed == 255 ) {
                triple.rgbtBlue = 0;
                triple.rgbtGreen = 0;
            }
            fwrite( &triple, sizeof( RGBTRIPLE ), 1, outptr );
        }

        // // skip over padding, if any
        // fseek( inptr, padding, SEEK_CUR );

        // // then add it back (to demonstrate how)
        // for ( int k = 0; k < padding; k++ ) {
        //     fputc( 0x00, outptr );
        // }
    }

    // close both files
    fclose( inptr );
    fclose( outptr );

    // success
    return 0;
}