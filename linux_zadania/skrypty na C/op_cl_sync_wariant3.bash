#!/bin/bash
# vim: sts=4 sw=4 et :

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
    exec 3> PIPE
    for zm in {100..10..4} ; do
	    echo $zm " " $((zm << 2))     >&3  
	    echo "LOG: $zm -> $(( zm * 4 ))"
    done 
)  &
 
# odbiorcy działający sekwencyjnie
( 
    exec 3< PIPE
    for (( zm=0; zm < K ; zm++ )) ; do 
        echo -e "\n--- dd #$((zm+1)) --- " ; dd bs=1 count=40 <&3 ; 
    done 
) &



# rodzic synchronizuje
wait

echo '--koniec--'
