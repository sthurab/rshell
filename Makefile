CC=g++
CC_FLAGS=-Wall -Werror -ansi -pedantic

all:
	mkdir -p ./bin	
	$(CC) $(CFLAGS) ./src/main.cpp -o ./bin/rshell

rshell:
	$(CC) $(CFLAGS) ./src/main.cpp

clean:
	rm -rf bin
	
	
