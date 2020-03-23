compile:
	gcc -c *.c

output:
	gcc -o siavm *.o

remove:
	rm -r *.o siavm