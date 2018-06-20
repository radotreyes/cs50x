#include <stdio.h>
#include <cs50.h>

void printRow( int count, int height ) {
    for( int i = 0; i < height; i++ ) printf( " " );
    for( int i = 0; i < count; i++ ) printf( "#" );
    printf( "  " );
    for( int i = 0; i < count; i++ ) printf( "#" );
    printf( "\n" );
}

int main( void ) {
    int height;
    while( 1 ) {
        height = get_int( "Enter a number between 0 and 23: ");
        if( height >= 0 && height < 24 ) break;
    }

    for( int i = 1; i < height + 1; i++ ) {
        printRow( i, height - i );
    }
}