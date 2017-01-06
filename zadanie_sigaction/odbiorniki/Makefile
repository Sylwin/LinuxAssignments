all : lampowy_1 lampowy_2 kwarcowy_1 kwarcowy_2

lampowy_1 : odbiornik_lampowy.c
	gcc -Wall -std=c89 odbiornik_lampowy.c -o lampowy_1

lampowy_2 : odbiornik_lampowy.c
	gcc -Wall -std=gnu99 odbiornik_lampowy.c -o lampowy_2

kwarcowy_1 : odbiornik.c
	gcc -Wall -std=c89 odbiornik.c -o kwarcowy_1

kwarcowy_2 : odbiornik.c
	gcc -Wall -std=gnu99 odbiornik.c -o kwarcowy_2


clean :
	rm -f lampowy_1 lampowy_2 kwarcowy_1 kwarcowy_2


