CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -pthread logger.o ghost.o

all: 	main building util hunter
		gcc -o a5 building.o util.o logger.o ghost.o hunter.o main.o	

main: 	main.c defs.h
		gcc -c main.c 

building: 	building.c defs.h
			gcc -c building.c 

util: 	util.c defs.h
		gcc -c util.c 

hunter: 	hunter.c defs.h
			gcc -c hunter.c 

clean:
	rm -f util.o building.o hunter.o main.o