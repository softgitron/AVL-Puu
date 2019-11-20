# Debugauksen voi poistaa tarvittaessa
# compile-flags = -Wall -Werror -ansi
compile-flags = -Wall -Werror -ansi -DDEBUG -g -O0

harjoitustyo: harjoitustyo.c tiedoston_kasittely.o puu.o tulostus.o kaannokset.o valikko.o
	gcc harjoitustyo.c tiedoston_kasittely.o puu.o tulostus.o kaannokset.o valikko.o $(compile-flags) -o harjoitustyo

puu.o: puu.c
	gcc puu.c -c $(compile-flags) -o puu.o

tiedoston_kasittely.o: tiedoston_kasittely.c
	gcc tiedoston_kasittely.c -c $(compile-flags) -o tiedoston_kasittely.o

tulostus.o: tulostus.c
	gcc tulostus.c -c $(compile-flags) -o tulostus.o

kaannokset.o: kaannokset.c
	gcc kaannokset.c -c $(compile-flags) -o kaannokset.o

valikko.o: valikko.c
	gcc valikko.c -c $(compile-flags) -o valikko.o

clean:
	rm -rf *.o