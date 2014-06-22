PROJECT=42sh
LEADER=pierra_j
TARFILES=src AUTHORS doc README TODO test Makefile configure CMakeLists.txt

.PHONY: all clean doc distclean dist 42sh check

all: 42sh

42sh:
	make -C build 42sh; \
	mv $(CURDIR)/build/42sh $(CURDIR)

clean:
	rm -rf build

distclean: clean
	rm -rf doc/latex doc/html
	rm -f 42sh
	rm -rf $(LEADER)-$(PROJECT).tar.bz2
	rm -rf $(LEADER)-$(PROJECT)

dist: distclean
	mkdir -p $(LEADER)-$(PROJECT)
	for name in "`git ls-files | sed -E 's/^(\w*?)\/.*/\1/' | uniq`"; do \
	cp -R $$name $(LEADER)-$(PROJECT)/; \
	done
	tar -cvjf $(LEADER)-$(PROJECT).tar.bz2 $(LEADER)-$(PROJECT)/
	rm -rf $(LEADER)-$(PROJECT)
doc:
	doxygen doc/Doxyfile

check: all
	cd test ; \
	python check.py

distcheck: 
	tar -xvf $(LEADER)-$(PROJECT).tar.bz2
	cd  $(LEADER)-$(PROJECT) && [ -x ./configure ] && ./configure && make check
