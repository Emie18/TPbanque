banque.exe : main.o fonctions.o
	gcc main.o fonctions.o -o banque.exe
main.o: main.c banque.h
	gcc -c main.c 
fonctions.o: fonctions.c banque.h
	gcc -c fonctions.c
clean:
	rm *.o *.exe