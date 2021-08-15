all: assembler main.o data.o firstpass.o secondpass.o symbols.o writefiles.o helpers.o check_error.o line_handler.o label_handler.o parameters_hundler.o read.o hash_table.o
assembler: main.o data.o firstpass.o secondpass.o symbols.o writefiles.o helpers.o check_error.o line_handler.o label_handler.o parameters_hundler.o read.o hash_table.o
	gcc -O0 -g -ansi -Wall -pedantic main.o data.o firstpass.o secondpass.o symbols.o writefiles.o helpers.o check_error.o label_handler.o parameters_hundler.o read.o line_handler.o hash_table.o -lm -o assembler
main.o: main.c data.h firstpass.h secondpass.h symbols.h writefiles.h globals.h helpers.h check_error.h
	gcc -O0 -g -c -ansi -Wall -pedantic main.c -o main.o
data.o: data.c 
	gcc -O0 -g -c -ansi -Wall -pedantic data.c -o data.o
firstpass.o: firstpass.c data.h secondpass.h symbols.h writefiles.h globals.h helpers.h
	gcc -O0 -g -c -ansi -Wall -pedantic firstpass.c -o firstpass.o 
secondpass.o: secondpass.c firstpass.h data.h symbols.h writefiles.h globals.h helpers.h
	gcc -O0 -g -c -ansi -Wall -pedantic secondpass.c -o secondpass.o
symbols.o: symbols.c helpers.h globals.h data.h writefiles.h
	gcc -O0 -g -c -ansi -Wall -pedantic symbols.c -o symbols.o
writefiles.o: writefiles.c globals.h firstpass.h secondpass.h symbols.h data.h helpers.h
	gcc -O0 -g -c -ansi -Wall -pedantic writefiles.c -o writefiles.o
helpers.o: helpers.c
	gcc -O0 -g -c -ansi -Wall -pedantic helpers.c -o helpers.o
check_error.o: check_error.c hash_table.h label_handler.h line_handler.h
	gcc -O0 -g -c -ansi -Wall -pedantic check_error.c -o check_error.o
line_handler.o: line_handler.c read.h label_handler.h parameters_hundler.h
	gcc -O0 -g -c -ansi -Wall -pedantic line_handler.c -o line_handler.o
label_handler.o: label_handler.c read.h
	gcc -O0 -g -c -ansi -Wall -pedantic label_handler.c -o label_handler.o
parameters_hundler.o: parameters_hundler.c read.h hash_table.h label_handler.h
	gcc -O0 -g -c -ansi -Wall -pedantic parameters_hundler.c -o parameters_hundler.o
read.o: read.c
	gcc -O0 -g -c -ansi -Wall -pedantic read.c -o read.o
hash_table.o: hash_table.c
	gcc -O0 -g -c -ansi -Wall -pedantic hash_table.c -o hash_table.o 

clean:
		rm *.o
		

	
	

	 
