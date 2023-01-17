## (GNU) Makefile for xgrk
##

CC=gcc
ARCH := $(shell uname -s)

CFLAGS=-O3 -s #-Wall
LFLAGS=-lX11 -lXpm  

#DEFS=-DNOXPM

ifeq ($(ARCH),Linux)
LIBS=-L/usr/X11R6/lib
INCL=
endif

ifeq ($(ARCH),FreeBSD)
LIBS=-L/usr/X11R6/lib
INCL=-I/usr/X11R6/include
endif

ifeq ($(ARCH),Darwin)
LIBS=-L/usr/X11R6/lib
INCL=-I/usr/X11R6/include
endif



all: xgrk xgrk2

xgrk:	xgrk.c xgrk.h 
	$(CC) $(CFLAGS) xgrk.c -o xgrk $(INCL) $(LIBS) $(LFLAGS)  $(DEFS)

xgrk2:	xgrk.c xgrk2.h 
	$(CC) $(CFLAGS) xgrk.c -o xgrk2 $(INCL) $(LIBS) $(LFLAGS)  $(DEFS)\
        -Dalth

clean:
	rm -f core xgrk xgrk2

