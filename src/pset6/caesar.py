import sys

def caesar( plaintext, key ):
    if int( key ) < 0:
        return

    plaintext_ascii = [ ( ord( char ) + int( key ) ) for char in plaintext ]
    for ascii in plaintext_ascii:
        if ( ascii < 97 and ascii > 90 ) or ascii > 122:
            ascii -= 25

    ciphertext = ''.join( [ chr( ascii ) for ascii in plaintext_ascii ] )
    print( 'ciphertext: {}'.format( ciphertext ) )

if __name__ == '__main__':
    if len( sys.argv ) is not 3:
        print( 'Usage: python caesar.py plaintext key' )
    else:
        caesar( sys.argv[1], sys.argv[2] )