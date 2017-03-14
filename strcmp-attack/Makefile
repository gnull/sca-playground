.PHONY: all

all: vulnerable timestamp

CFLAGS = -std=gnu99

timestamp: timestamp.c
	gcc $(CFLAGS) -O3 -o $@ $^

# CFLAGS += -O2
