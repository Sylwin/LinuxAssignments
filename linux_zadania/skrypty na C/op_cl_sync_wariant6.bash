#!/bin/bash
# vim: sts=4 sw=4 et :
# :: AzBvCnDłEnF GoHlIćJ KfLlMaNpOuPeQbRaSvTmUnVpWwXnY, ZnA BgChD
# :: EeFbGmHpImJnKeLbMjNnOaPvQrR 

# *** dlaczego, mimo zastosowania takiego samego mechanizmu jak w wariancie 1,
#     nie działa synchronizacja (czyli w tym przypadku - nie zawisł)?

# pierwszy (i jedyny) parametr: ilość konsumentów
# domyślnie jeden
if [[ -z $1 ]] ; then 
    K=1
else 
    K=$1
fi

rm -f PIPE
mkfifo PIPE
trap "rm PIPE" EXIT

# nadwaca 
( 
    for zm in {100..10..4} ; do
	    echo $zm " " $((zm << 2))     > PIPE 
	    echo "LOG: $zm -> $(( zm * 4 ))"
    done 
)  &
 
# odbiorca
nl < PIPE &



# rodzic synchronizuje
wait

echo '--koniec--'

# :: AnByCrD EjFlGfHgInJeKpLmMlN OqPbQqRnSćT UfVyWrXrYcZ 0 
