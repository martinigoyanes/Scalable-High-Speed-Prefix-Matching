SRC = my_route_lookup.c io.c io.h utils.c utils.h	hashtable.c	hashtable.h	binarytree.c	binarytree.h	tools.c	tools.h
#CFLAGS = -Wall -O3
CFLAGS = -Wall	-ggdb

all: my_route_lookup

my_route_lookup: $(SRC)
	gcc $(CFLAGS) $(SRC) -o my_route_lookup -lm

.PHONY: clean

clean:
	rm -f my_route_lookup

#RL Lab 2020 Switching UC3M
