CC=gcc
CFLAGS=-Wall
CSOURCE=fslice.c
CHEADER=fslice.h
BIN=../bin/fslice

all: $(BIN)

$(BIN): $(CSOURCE) $(CHEADER)
	$(CC) $(CSOURCE) $(CFLAGS) -o $(BIN)
