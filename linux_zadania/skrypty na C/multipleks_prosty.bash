#!/bin/bash
# vim: sts=4 sw=4 et :

# pierwszy parametr - łańcuch z parametrami dla konsumentów (ilości
#  wczytywanych linii)
# drugi parametr - łańcuch z parametrami dla producentów (kolejne czasy
#   opóźnieńi)
# brak parametrów -> wartości domyślne:
#  jeden konsument - 15 linii
#  jeden producenti - 2 sek

if [[ -z $1 ]] ; then 
    K=( 15 )
else 
    K=( $1 )
fi
if [[ -z $2 ]] ; then 
    P=( 2 )
else 
    P=( $2 )
fi
# DEBUG
# echo "konsumenty: ${K[@]}"
# echo "producenty: ${P[@]}"


rm -f PIPE
mkfifo PIPE
trap "rm PIPE" EXIT
# *** jaki jest cel zastosowania poniższej pułapki?
# *** jak przebiega scenariusz jej zastosowania?
trap "kill 0"  INT

producent () {
	echo "producent $BASHPID"
	while : ; do
		R=$((RANDOM % 40))
		for ((zm=$R; zm <=40; zm ++ )) ; do
			echo "-- $zm --" 1>&2
			echo "PROD:$BASHPID ($zm)"
			sleep $1
		done
	done 
}


konsument () {
    echo "konsument $BASHPID (x$1)"
    zm=0
    while (( $zm < $1 )) ; do
        if read line ; then 
            echo -e "$BASHPID:($zm)\t$line"
            (( zm+= 1))
        else 
            echo "err $BASHPID"
            zm=$1
        fi
    done 
}

for i in "${P[@]}" ; do 
    producent $i  2> PIPE & 
done
for i in "${K[@]}" ; do 
    konsument $i < PIPE & 
done

until wait ; do : ; done


