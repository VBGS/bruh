CC ?= gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -o

all: bruh rainbruh

rainbruh: rainbruh.c
	@$(CC) $(CFLAGS) $@ $<

bruh: bruh.c
	@$(CC) $(CFLAGS) $@ $<

clean:
	@rm -f bruh rainbruh

test: bruh
	@./$< 64 128 64

.PHONY: all test clean