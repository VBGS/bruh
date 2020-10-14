CC ?= gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -o

bruh: bruh.c
	@$(CC) $(CFLAGS) $@ $<

clean:
	@rm -f bruh

test: bruh
	@./$< 64 128 64