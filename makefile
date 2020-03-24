compile:
	gcc -c *.c

output:
	gcc -o siavm *.o

debug:
	gcc -g -o siavm *.c

remove:
	rm -rf *.o siavm ./siavm.dSYM
