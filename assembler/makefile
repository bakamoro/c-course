assembler: main.o data.o firstpass.o secondpass.o symbols.o writefiles.o helpers.o
	gcc -g -ansi -Wall -pedantic main.o data.o firstpass.o secondpass.o symbols.o writefiles.o helpers.o -lm -o assembler
main.o: main.c data.h firstpass.h secondpass.h symbols.h writefiles.h globals.h helpers.h
	gcc -c -ansi -Wall -pedantic main.c -o main.o
data.o: data.c 
	gcc -c -ansi -Wall -pedantic data.c -o data.o
firstpass.o: firstpass.c data.h secondpass.h symbols.h writefiles.h globals.h helpers.h
	gcc -c -ansi -Wall -pedantic firstpass.c -o firstpass.o 
secondpass.o: secondpass.c firstpass.h data.h symbols.h writefiles.h globals.h helpers.h
	gcc -c -ansi -Wall -pedantic secondpass.c -o secondpass.o
symbols.o: symbols.c helpers.h globals.h data.h writefiles.h
	gcc -c -ansi -Wall -pedantic symbols.c -o symbols.o
writefiles.o: writefiles.c globals.h firstpass.h secondpass.h symbols.h data.h helpers.h
	gcc -c -ansi -Wall -pedantic writefiles.c -o writefiles.o
helpers.o: helpers.c
	gcc -c -ansi -Wall -pedantic helpers.c -o helpers.o
	 
