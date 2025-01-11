BIN = libdrawcli.so
CC = gcc
CFILES = drawcli.c
CFLAGS = -Wall -Wextra -std=c99 -shared

$(BIN): $(CFILES)
	$(CC) -o $(BIN) $(CFLAGS) $(CFILES)

.PHONY: testing

testing: $(BIN)
	$(CC) -o test -L. -ldrawcli test.c
