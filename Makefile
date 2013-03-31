CC=gcc
CFLAGS= -g -Wall

all: tdmctl

evmctl: tdmctl.c
	$(CC) $(CFLAGS) -o tdmctl tdmctl.c

install:
	cp tdmctl /bin/

clean:
	rm tdmctl
