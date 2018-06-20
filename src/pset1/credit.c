#include <stdio.h>
#include <cs50.h>

long long pop( long long number, int count ) {
    for( int i = 0; i < count; i++ ) {
        number = (number - (number % 10)) / 10; // this pattern removes a digit from a number
    }

    return number;
}

int getDigitCount( long long number ) {
    int n = 0;
    while( number ) {
        number = (number - (number % 10)) / 10; // this pattern removes a digit from a number
        n++;
    }

    return n;
}

int main( void ) {
    long long cardNumber;
    while( 1 ) {
        cardNumber = get_long_long( "Enter your credit card number: ");
        if( sizeof( cardNumber ) == 8 ) break;
    }
    /* visa cards can have the fewest digits at 13, so
     * remove 12 digits so we can validate the initial sequence
     */
    int cardOpeningSeq = pop( cardNumber, 12 );
    int cardIsValid = 0;
    char* cardType = "INVALID\n";

    switch( getDigitCount( cardOpeningSeq ) ) {
        case 1:
            if( cardOpeningSeq == 4 ) {
                cardIsValid = 1;
                cardType = "VISA\n";
            }
            break;
        case 3:
            cardOpeningSeq = (int)( pop( (long long)cardOpeningSeq, 1 ) );
            if( cardOpeningSeq == 34 || cardOpeningSeq == 37 ) {
                cardIsValid = 1;
                cardType = "AMEX\n";
            }
            break;
        case 4:
            cardOpeningSeq = (int)( pop( (long long)cardOpeningSeq, 2 ) );
            if( cardOpeningSeq >= 51 && cardOpeningSeq <= 55 ) {
                cardIsValid = 1;
                cardType = "MASTERCARD\n";
            }
            else if( (int)( pop( (long long)cardOpeningSeq, 1 ) ) == 4 ) {
                cardIsValid = 1;
                cardType = "VISA\n";
            }
            break;
    }

    if( cardIsValid ) {
        int checksum = 0;
        int sum = 0;

        while( cardNumber ) {
            sum += (int)( cardNumber % 10 );
            cardNumber = pop( cardNumber, 1 );

            int product = (int)( (cardNumber % 10) * 2 );
            if( getDigitCount( product ) == 2 ) {
                checksum += product % 10;

                product = (product - (product % 10)) / 10;
                checksum += product;
            }
            else {
                checksum += product; // double and add to checksum
            }

            cardNumber = pop( cardNumber, 1 );
        }

        checksum += sum;
        if( checksum % 10 ) {
            cardType = "INVALID\n";
        }
    }

    printf( "%s", cardType );
    return 0; // required
}