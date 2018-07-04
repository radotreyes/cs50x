from functools import reduce
import re

def validate():
    # constants
    VALID_INITIAL_SEQUENCES = { '3': 'AMEX','4': 'VISA', '5': 'MASTERCARD' }
    INVALID = 'INVALID'

    # get input
    cc = input( 'Credit card number: ' )
    cc_type = INVALID # init to invalid at first

    # validate based on length only
    if len( cc ) is not 13 and len( cc ) is not 15 and len( cc ) is not 16:
        print( INVALID )
        return

    # validate based on first digits only
    init_sequence = re.search( '^4|^5[1-5]|^3[47]', cc )
    try:
        cc_type = VALID_INITIAL_SEQUENCES[init_sequence.group()[0]]
    except KeyError:
        print( INVALID )
        return

    # validate based on Luhn's algorithm
    cc_list = list( cc[::-1] )
    doubled = list( map(
        lambda n: int( n[1] ) * 2,
        list( filter( lambda x: ( x[0] % 2 ), enumerate( cc_list ) ) )
    ) )
    dd = []
    for number in doubled:
        for char in str( number ):
            dd.extend( char )

    dsummed = reduce( lambda a, b: int( a ) + int( b ), dd )
    summed = reduce( lambda c, d: c + d, list( map(
        lambda p: int( p[1] ),
        list( filter( lambda y: not( y[0] % 2 ), enumerate( cc_list ) ) )
    ) ) )
    check = ( dsummed + summed ) % 10
    print( INVALID ) if check else print( cc_type )

if( __name__ == '__main__' ):
    validate()
