/*
 * consts.h
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

//XXX: NOTA: da dei problemi. A volte bisogna usare /usr/local/bin invece di /usr/bin

#ifndef __CONSTS__
#define __CONSTS__

#define IS_JBT		".jbt"
#define JBT_COMPILER	"/usr/bin/jb2tex"
#define SKIP_FOLDER	"skip_this"
#define LATEX_COMPILER	"/usr/local/bin/pdflatex"
#define BIBTEX_COMPILER "/usr/local/bin/bibtex"
#define MAKEINDEX_COMP 	"/usr/local/bin/makeindex"

#define ARG_MAX		_POSIX_ARG_MAX

#define makejbt(file)	do_argv(2,JBT_COMPILER,file)
#define IS_FILE(file)	(file_exists(file,NULL,NULL,NULL)==1)
#define IS_DIR(file)	(file_exists(file,NULL,NULL,NULL)==2)

#endif
