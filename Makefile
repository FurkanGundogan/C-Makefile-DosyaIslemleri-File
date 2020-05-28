randevu: main.o libRandevu.o
	gcc main.o libRandevu.o -o randevu

main.o: main.c
	gcc -c main.c

libRandevu.o: libRandevu.c libRandevu.h
	gcc -c libRandevu.c

clean:
	del *.o randevu.exe
run:
	randevu.exe
