CFlags:=-Wall

all: Uhrzeit


Funktionen.o:Funktionen.c Funktionen.h 
	gcc $(CFlags) -o Funktionen.o -c Funktionen.c

Uhrzeit: Uhrzeit.c Funktionen.o
	gcc $(CFlags) -o Uhrzeit Uhrzeit.c Funktionen.o

clean:
	rm Funktionen.o
	rm Uhrzeit
