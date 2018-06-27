#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main( int argc, char* argv[] ) {
    // ensure proper usage
    if ( argc != 4 ) {
        fprintf( stderr, "Usage: float to_resize resized\n" );
        fprintf( stderr, "  * float must be a floating point number between ( 0, 100 ]\n" );
        return 1;
    }

    // remember filenames
    float scale = atof( argv[1] );
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file
    FILE* inptr = fopen(infile, "r");
    if( inptr == NULL ) {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if( outptr == NULL ) {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER and BITMAPINFOHEADER
    BITMAPFILEHEADER bf;
    BITMAPINFOHEADER bi;
    fread( &bf, sizeof( BITMAPFILEHEADER ), 1, inptr );
    fread( &bi, sizeof( BITMAPINFOHEADER ), 1, inptr );

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if( bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0 ) {
        fclose( outptr );
        fclose( inptr );
        fprintf( stderr, "Unsupported file format.\n" );
        return 4;
    }
    // modify the file and info headers based on specified user scale
    fprintf( stderr, "%x\n", bf.bfSize );
    bf.bfSize *= scale;
    fprintf( stderr, "%x\n", bf.bfSize );
    bi.biWidth *= scale;
    bi.biHeight *= scale;

    // write outfile's BITMAPFILEHEADER and BITMAPINFOHEADER
    fwrite( &bf, sizeof( BITMAPFILEHEADER ), 1, outptr );
    fwrite( &bi, sizeof( BITMAPINFOHEADER ), 1, outptr );

    // determine padding for scanlines
    int padding = ( 4 - ( bi.biWidth * sizeof( RGBTRIPLE ) ) % 4 ) % 4;

    // iterate over infile's scanlines
    for( int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++ ) {
        /* MULTIPLY HEIGHT
         * write a given scanline as many times as specified by scale,
         * rounding down
         */
        for( int k = 0; k < ( int ) scale; k++ ) {
            for( int j = 0; j < bi.biWidth; j++ ) {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread( &triple, sizeof( RGBTRIPLE ), 1, inptr );

                /* MULTIPLY WIDTH */
                // write RGB triple to outfile as many times as specified by scale,
                // rounding down to avoid segfault
                for( int h = 0; h < ( int ) scale; h++ ) {
                    fwrite( &triple, sizeof( RGBTRIPLE ), 1, outptr );
                }
            }

            // skip over padding, if any
            fseek( inptr, padding, SEEK_CUR );

            // then add it back (to demonstrate how)
            for( int l = 0; l < ( int ) scale; l++ ) {
                for( int m = 0; m < padding; m++ ) {
                    fputc( 0x00, outptr );
                }
            }
        }
    }

    // close infile
    fclose( inptr );

    // close outfile
    fclose( outptr );

    // success
    return 0;
}
