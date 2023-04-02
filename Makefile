CC= gcc
CFLAGS= -g

OUT= ftree

COMMON_C= src/main.c \
src/ftree.c

COMMON_O= main.o \
ftree.o

# generator program
PROJ= src/generate/Program.cs

all: base generator

base:
	$(CC) $(CFLAGS) -L src -c $(COMMON_C)
	$(CC) $(CFLAGS) -L src -o $(OUT) $(COMMON_O)

generator:
ifeq ($(OS),Windows_NT)
	C:\Windows\Microsoft.NET\Framework\v4.0.30319\csc.exe /t:exe /out:generate.exe $(subst /,\,$(PROJ))
else
	csc /t:exe /out:generate.exe $(PROJ)
endif