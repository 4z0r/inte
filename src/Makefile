#Done by	Ovidiu - Dan Bogat

CFLAGS=-Wall -g -O2
CC=cc
LIBS=
BINDIR=./../bin

SOURCEFILES=main.C functions.C cfgparse.C
HEADERS=main.H functions.H debug.H cfgparse.H


all inte: $(SOURCEFILES) $(HEADERS)
	$(CC) $(CFLAGS) $(SOURCEFILES) -o $(BINDIR)/inte $(LIBS)

check: $(SOURCEFILES) $(HEADERS)
	$(CC) -DTEST $(CFLAGS) $(SOURCEFILES) -o $(BINDIR)/inte $(LIBS)
