BIN = libdrawcli.so
CC = gcc
CFILES = drawcli.c turtle.c
CFLAGS = -Wall -Wextra -std=c99
BIN_CFLAGS = $(CFLAGS) -fPIC -shared
DEMOS_CFLAGS = $(CFLAGS) -L. -ldrawcli -lm
DEMOS = demos/viewer demos/turtle demos/shapes

all: $(BIN) $(DEMOS)

$(BIN): $(CFILES)
	$(CC) -o $(BIN) $(BIN_CFLAGS) $(CFILES)

$(DEMOS): %: %.c
	$(CC) -o $@ $(DEMOS_CFLAGS) $<

clear:
	rm -f $(DEMOS) $(BIN)
