all:
	ocamlc -c debug.mli debug.ml
	ocamlyacc texrule.mly
	ocamlc -c texrule.mli
	ocamllex  texcomp.mll
	ocamlc -c texcomp.ml
	ocamlc -c texrule.ml
	ocamlc -c compiler.ml
	ocamlc -o jb2tex debug.cmo texcomp.cmo texrule.cmo compiler.cmo 
	make cleanout

cleanout:
	rm -f tex*.ml
	rm -f *.o
	rm -f *.cm*
	

clean:	cleanout
	rm -f jb2tex

install:
	sudo cp jb2tex /usr/bin
