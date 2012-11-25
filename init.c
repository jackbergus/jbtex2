/*
 * init.c
 * This file is part of jbtex2
 *
 * Copyright (C) 2012 - Giacomo Bergami <giacomo90@libero.it>
 *
 * jbtex2 is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * jbtex2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with jbtex2; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, 
 * Boston, MA  02110-1301  USA
 */


#include "recursive.h"
#include "make.h"

#define MKJBT 1
#define MKMIN 2
#define ARG1_IS(const) ((argc>=2)&&(strcmp(argv[1],const)==0))
#define ARG2_IS(const) ((argc>=3)&&(strcmp(argv[2],const)==0))

void help();

int main(int argc, char *argv[])
{
	if (argc <= 1) {
		help();
		exit(1);
	}
	
	if (ARG1_IS("clean")) 
		clean_all();
	else if (ARG1_IS("mkjbt"))
		mkjbt();
	else if (ARG1_IS("main"))
		mkmain(NULL);
	else if (ARG1_IS("make"))
		mkworld();
	else if ((ARG1_IS("mkworld"))) {
		clean_all();
		mkjbt();
		mkmain(NULL);
		mkworld();
	}
	else if ((ARG1_IS("stophere"))) {
		FILE *f = fopen(SKIP_FOLDER,"w+");
		fclose(f);
	}
	else help();
}
