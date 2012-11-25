all:	
	cd ocaml-parser && make
	gcc -c -Iinclude recursive.c
	gcc -c -Iinclude mkjbt.c
	gcc -c -Iinclude mkmain.c
	gcc -c -Iinclude init.c
	gcc -c -Iinclude compile.c
	gcc -c -Iinclude support.c
	gcc -o jbtex2 *.o
	rm -f *.o
	
clean:
	rm -f *.o
	rm -f jbtex2 jbtex
	cd ocaml-parser && make clean

virgin: clean
	rm -f Makefile.in Makefile
	rm -f ocaml-parser/Makefile.in ocaml-parser/Makefile
	rm -f config.* missing configure

install:	all
	cd ocaml-parser && make install
	sudo cp jbtex2 /usr/bin/jbtex2
	
