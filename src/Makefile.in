#Done by	Ovidiu - Dan Bogat

CFLAGS=-Wall -g -O2
CC=g++
LIBS=-lcolt
BINDIR=./../bin
COND=

SOURCEFILES=main.C functions.C cfgparse.C sockets.C
HEADERS=main.H functions.H cfgparse.H sockets.H

install: all
	install -d $(prefix);
	install -m 0755 ./../bin/inte $(prefix);
	install -d /usr/lib;
	install -m 0755 ./libcolt.so /usr/lib;
	-rm ./libcolt.so;
	-rm ./colors_table.o;
	gzip -c ./../man/inte > /usr/share/man/man1/inte.1.gz

uninstall:
	-rm $(prefix)/inte
	-rm /usr/lib/libcolt.so
	-rm /usr/share/man/man1/inte.1.gz

all inte: colt_lib $(SOURCEFILES) $(HEADERS)
	$(CC) $(COND) -L$(slibpref) -Wl,-rpath=$(slibpref) $(CFLAGS) $(SOURCEFILES) -o $(BINDIR)/inte $(LIBS)

check: colt_lib $(SOURCEFILES) $(HEADERS)
	$(CC) -DTEST -L$(slibpref) -Wl,-rpath=$(slibpref) $(CFLAGS) $(SOURCEFILES) -o $(BINDIR)/inte $(LIBS)

colt_lib: colors_table.H colors_table.C
	$(CC) -fPIC -c colors_table.C -o colors_table.o
	$(CC) -shared -o libcolt.so colors_table.o

Makefile: Makefile.in ./../config.status
	cd .. && ./config.status src/$@

./../config.status: ./../configure
	cd .. && ./config.status --recheck
