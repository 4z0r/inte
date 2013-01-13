project=inte
version=1.0
distdir=$(project)-$(version)
tarball=$(distdir).tar.gz

all inte check colt_lib:

	if [ `tput colors` -ge '8' ];then\
		cd src && $(MAKE) $@ COND=-DCOLORS;\
	else\
		cd src && $(MAKE) $@;\
	fi

	rm -rf ./inte &> /dev/null;
	ln -s ./bin/inte ./inte;

clean:	FORCE
	rm -rf ./bin/inte &> /dev/null;
	rm -rf ./inte &> /dev/null;
	rm -rf ./src/*.o &> /dev/null;
	rm -rf ./src/*.so &> /dev/null;

distcheck: dist
	tar -xzvf $(tarball);
	cd $(distdir) && $(MAKE) check && ./inte;
	cd ..;
	rm -rf $(tarball) &> /dev/null;
	rm -rf $(distdir) &> /dev/null;
	@echo "*** Project set up and ready for distribution. ***";
	@echo "*** Type 'make dist' to pack it up. ***"

dist:	$(tarball)

$(tarball): $(distdir)
	rm -rf $(tarball) &> /dev/null;
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
	rm -rf $(distdir) &> /dev/null;
	rm -rf $(tarball) &> /dev/null;

.PHONY: clean FORCE 
