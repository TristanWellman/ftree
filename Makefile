CC= gcc
CFLAGS= -g

OUT= ftree

COMMON_C= src/main.c \
src/ftree.c

COMMON_O= main.o \
ftree.o

all: base

base:
	$(CC) $(CFLAGS) -L src -c $(COMMON_C)
	$(CC) $(CFLAGS) -L src -o $(OUT) $(COMMON_O)