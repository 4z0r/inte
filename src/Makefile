#Done by	Ovidiu - Dan Bogat

CFLAGS=-Wall -g -O2
CC=g++
LIBS=-lcolt
LIBDIR=/home/ovidiu/code/inte/src
BINDIR=./../bin
COND=

SOURCEFILES=main.C functions.C cfgparse.C sockets.C
HEADERS=main.H functions.H cfgparse.H sockets.H

all inte: colt_lib $(SOURCEFILES) $(HEADERS)
	$(CC) $(COND) -L$(LIBDIR) $(CFLAGS) $(SOURCEFILES) -o $(BINDIR)/inte $(LIBS)

check: colt_lib $(SOURCEFILES) $(HEADERS)
	$(CC) -DTEST -L$(LIBDIR) $(CFLAGS) $(SOURCEFILES) -o $(BINDIR)/inte $(LIBS)

colt_lib: colors_table.H colors_table.C
	$(CC) -fPIC -c colors_table.C -o colors_table.o
	$(CC) -shared -o libcolt.so colors_table.o
