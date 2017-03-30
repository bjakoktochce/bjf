bjf: main.c
	gcc -o bjf main.c -I.
install:
	install -m 0755 bjf /usr/bin
clean:
	rm -f *.o bjf
