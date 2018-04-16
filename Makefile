CC=gcc
CFLAGS=-g -O3
CFLAGS_AFT=-lm

all: check

default: check

clean:
	rm -rf *.o ram cache

cache: cache.o
	$(CC) $(CFLAGS) $< -o $@ $(CFLAGS_AFT)

ram: ram.c
	gcc ram.c -o ram

gdb_cache: cache
	gdb ./cache_calc

gdb_ram: ram
	gdb ./ram

%.o: %.c
	$(CC) $(CFLAGS) $< -c -o $@ $(CFLAGS_AFT)

check-cache: clean cache
	./cache

check: clean cache
	./cache

check-ram: clean ram
	./ram
