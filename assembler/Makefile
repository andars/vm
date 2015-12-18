CFLAGS = -Wall -std=c99


SOURCES = $(wildcard *.c)
HEADERS = $(wildcard *.h)
OBJECTS = $(SOURCES:.c=.o)

.PHONY: all

all: assembler

assembler: $(OBJECTS)
	$(CC) $(CFLAGS) -o assembler $^

%.o: %.c 
	$(CC) -c $(CFLAGS) -o $@ $<

