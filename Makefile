#Done by 	Ovidiu - Dan Bogat

# Makefile.  Generated from Makefile.in by configure.

project=inte
version=1.0
tarball=inte-1.0.tar.gz
distdir=$(project)-$(version)

prefix=/usr/bin
export prefix

slibpref=$${PWD}
export slibpref

all inte colt_lib install uninstall:

	if [ `tput colors` -ge '8' ];then\
		cd src && $(MAKE) $@ COND=-DCOLORS;\
	else\
		cd src && $(MAKE) $@;\
	fi

	rm -rf ./inte &> /dev/null;
	ln -s ./bin/inte ./inte;

check:
	if [ `tput colors` -ge '8' ];then\
		cd src && $(MAKE) check COND=-DCOLORS;\
	else\
		cd src && $(MAKE) check;\
	fi

	rm -rf ./inte &> /dev/null;
	ln -s ./bin/inte ./inte;
	./inte;
	rm -rf ./bin/inte;
	rm -rf ./inte;

clean:	FORCE
	rm -rf ./bin/inte &> /dev/null;
	rm -rf ./inte &> /dev/null;
	rm -rf ./src/*.o &> /dev/null;
	rm -rf ./src/*.so &> /dev/null;

distcheck: dist
	tar -xzvf $(tarball);
	cd $(distdir) && ./configure
	cd $(distdir) && $(MAKE) check;
	rm -rf $(tarball) &> /dev/null;
	rm -rf $(distdir) &> /dev/null;
	@echo "*** Project set up and ready for distribution. ***";
	@echo "*** Type 'make dist' to pack it up. ***";

dist:	$(tarball)

$(tarball): $(distdir)
	rm -rf $(tarball) &> /dev/null;
	tar cfz $(tarball) $(distdir)
	rm -rf $(distdir)

$(distdir): FORCE
	mkdir -p $(distdir)/bin;
	mkdir -p $(distdir)/log/valgrind;
	cp -R man $(distdir);
	cp -R src $(distdir);
	cp Makefile.in $(distdir);
	cp AUTHORS $(distdir);
	cp INSTALL $(distdir);
	cp NEWS $(distdir);
	cp CHANGELOG $(distdir);
	cp TODO $(distdir);
	cp -R log/valgrind $(distdir)/log;
	cp -R scripts $(distdir);
	cp ./vg $(distdir);
	cp ./mlog $(distdir);
	cp configure.ac $(distdir)
	cp configure $(distdir)
	cp config.h.in $(distdir)
	cp install-sh $(distdir)

FORCE:
	rm -rf $(distdir) &> /dev/null;
	rm -rf $(tarball) &> /dev/null;

Makefile: Makefile.in config.status
	./config.status $@

config.status: configure
	./config.status --recheck

.PHONY: clean FORCE all inte check colt_lib dist distcheck $(tarball) $(distdir) install uninstall
