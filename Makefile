mypreprocessor: main.o output.o comment_removal.o file_inclusion.o macro_replace.o macro_argument.o
	gcc main.o output.o comment_removal.o file_inclusion.o macro_replace.o macro_argument.o -o mypreprocessor

main.o: main.c preprocessor.h
	gcc -c main.c

output.o: output.c preprocessor.h
	gcc -c output.c

comment_removal.o: comment_removal.c preprocessor.h
	gcc -c comment_removal.c

file_inclusion.o: file_inclusion.c preprocessor.h
	gcc -c file_inclusion.c

macro_replace.o: macro_replace.c preprocessor.h
	gcc -c macro_replace.c

macro_argument.o: macro_argument.c preprocessor.h
	gcc -c macro_argument.c

clean:
	rm -f *.o

