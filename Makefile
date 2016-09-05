CC=gcc
CFLAGS=-Wall -Werror -std=c99 -c
INC=-I.
LFLAGS=-g
SRC=$(wildcard ./*.c)
OBJ=$(addprefix ./,$(notdir $(SRC:.c=.o)))

all: main

main: $(OBJ)
	$(CC) $^ -o $@ $(LFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) $< -o $@ -g

clean:
	rm -rf *.o
	rm -rf main
