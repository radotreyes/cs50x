if( __name__ == '__main__' ):
    max_height = None # initialize max_height to be invalid at first
    while max_height == None or max_height not in range( 0, 24 ):
        try:
            max_height = int( input( 'Enter a pyramid height: ' ) )
        except ValueError: # handle non-integer inputs
            continue

    # print a pyramid in specified range, incrementing 1 to avoid printing an empty row
    for height in range( 1, max_height + 1 ):
        print( '{0}{1}  {1}'
            .format( ' ' * ( max_height - height ), '#' * height )
        )