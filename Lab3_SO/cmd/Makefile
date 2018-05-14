CC=gcc
CFLAGS=-I.
DEPS=parser.h
OBJ=parser.o cmd.o

%.o: %.c $(DEPS)
	$(CC) -Wall -c -o $@ $< $(CFLAGS)

# Makefile example
cli: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f cli $(OBJ) *~

