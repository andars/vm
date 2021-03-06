CFLAGS = -Wall -Werror -std=c99


SOURCES = $(wildcard *.c)
HEADERS = $(wildcard *.h)
OBJECTS = $(SOURCES:.c=.o)

.PHONY: all

all: vm assembler

assembler:
	$(MAKE) -C assembler


vm: $(OBJECTS)
	$(CC) $(CFLAGS) -o vm $^

%.o: %.c 
	$(CC) -c $(CFLAGS) -o $@ $<

