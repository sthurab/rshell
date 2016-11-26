CC=g++
CC_FLAGS=-Wall -Werror -ansi -pedantic

all:
	$(CC) $(CFLAGS) main.cpp -o rshell

rshell:
	$(CC) $(CFLAGS) main.cpp

clean:
	rm rshell
	
	
