# Michał Radecki mr371591
# IPP - Pierwsze zadanie zaliczeniowe "Szpital"

hospital: hospital.o structure.o parse.o
	gcc -o hospital hospital.o structure.o parse.o
hospital.o : hospital.c structure.o parse.o
	gcc -c hospital.c
structure.o: structure.c parse.o
	gcc -c structure.c
parse.o: parse.c
	gcc -c parse.c
debug: hospital.o structure.o parse.o
	gcc -g -o hospital.dbg hospital.o structure.o parse.o
clean:
	rm -f *.o
	rm -f *.dbg
	rm -f hospital
