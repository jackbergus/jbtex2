#include "recursive.h"

void help() {
	printf("jbtex2 : Giacomo Bergami (c) 2011-2012\n");
	printf("--------------------------------------\n\n");
	printf("jbtex clean\t Cleans all the output files, except the pdf\n");
	printf("jbtex mkjbt\t Compiles all the .jbt in .jbt.tex\n");
	printf("jbtex main\t Creates all the main.tex files\n");
	printf("jbtex make\t Creates the main.pdf from main.tex\n");
	printf("jbtex mkworld\t Does all the upper procedures\n");
	printf("\n\n");
	printf("jbtex stophere\t Doesn't allow to surf inside the current folder\n\n");
}
