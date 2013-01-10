all inte:
	cd src && $(MAKE) $@;
	rm -rf ./inte 2> /dev/null
	ln -s ./bin/inte ./inte

clean:
	rm -rf ./bin/inte 2> /dev/null;
	rm -rf ./inte 2> /dev/null;

.PHONY: clean
