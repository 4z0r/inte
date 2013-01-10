project=inte
version=1.0
distdir=$(project)-$(version)
tarball=$(distdir).tar.gz

all inte:
	cd src && $(MAKE) $@;
	rm -rf ./inte 2> /dev/null
	ln -s ./bin/inte ./inte

clean:	FORCE
	rm -rf ./bin/inte 2> /dev/null;
	rm -rf ./inte 2> /dev/null;

distcheck: dist
	tar -xzvf $(tarball);
	cd $(distdir) && make && ./inte;
	cd ..;
	rm -rf $(tarball) 2> /dev/null;
	rm -rf $(distdir) 2> /dev/null;
	@echo "*** Project set up and ready for distribution. ***";
	@echo "*** Type 'make dist' to pack it up. ***"

dist:	$(tarball)

$(tarball): $(distdir)
	rm -rf $(tarball) 2> /dev/null;
	tar cfz $(tarball) $(distdir)
	rm -rf $(distdir)

$(distdir): FORCE
	mkdir -p $(distdir)/bin;
	mkdir -p $(distdir)/man;
	cp -R src $(distdir);
	cp Makefile $(distdir);
	cp AUTHORS $(distdir);
	cp INSTALL $(distdir);
	cp NEWS $(distdir);
	cp CHANGELOG $(distdir);
	cp TODO $(distdir);

FORCE:
	rm -rf $(distdir) 2> /dev/null;
	rm -rf $(tarball) 2> /dev/null;

.PHONY: clean FORCE
