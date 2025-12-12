all: program

program: main.c smartarray.c
	gcc -o program main.c smartarray.c

clean:
	rm -f program