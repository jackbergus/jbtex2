/*
 * compile.c
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

int reckon_mtc(const char* prova) {
	int i;
	for (i=strlen(prova)-1; i>=0; i--) {
		if (!isdigit(prova[i])) break;
	}
	return ((i-3>=0)&&(prova[i]=='c')&&(prova[i-1]=='t')&&(prova[i-2]=='m')&&(prova[i-3]=='.'));
}

int select_toclean(const struct dirent *entry)
{
   printf("%s\n",entry->d_name);
   if ((entry->d_type==DT_REG) && ((check_extension(entry->d_name,".aux"))
                               || (check_extension(entry->d_name,".idx"))
                               || (check_extension(entry->d_name,".ind"))
                               || (check_extension(entry->d_name,".ilg"))
                               || (check_extension(entry->d_name,".log"))
                               || (check_extension(entry->d_name,".maf"))
                               || (check_extension(entry->d_name,".mtc"))
                               || (check_extension(entry->d_name,".out"))
                               || (check_extension(entry->d_name,".toc"))
                               || (check_extension(entry->d_name,".log"))
                               || (check_extension(entry->d_name,".bbl"))
                               || (check_extension(entry->d_name,".blg"))
                               || (reckon_mtc(entry->d_name))))
     return (1);
   else
     return (0);
}

/** clean_all():
 *  Cleans all the main path
 */
void clean_all(void)
{
           struct dirent **namelist;
           int n, i=0;
           int mainv = 0;

	   if (file_exists("preamb.tex",NULL,NULL,NULL)) {
		   n = scandir( ".", &namelist, select_toclean, alphasort);
		   if (n < 0)
		       perror("scandir (toclean)");
		   else {
		       for (i=0; i<n; i++)  {
		       	   printf("....%s\n",namelist[i]->d_name);
		           unlink(namelist[i]->d_name);
		           free(namelist[i]);
		       }
		       free(namelist);
		   }
	   }

}

#define run(cmd) 	{ runcommand(cmd); }

/** mkworld():
 *  Compiles the sources, and eventually builds with biblatex
 */
void mkworld() {
	//struct stat okbiblio;
	
	do_argv(2,LATEX_COMPILER,"main.tex");
	
	if (IS_FILE("main.idx")) {
		printf("\033[35mThere is main.idx...\033[0m\n");
		do_argv(2,MAKEINDEX_COMP,"main.idx");
		
	}
	
	do_argv(2,BIBTEX_COMPILER,"main.aux");
	
	do_argv(2,LATEX_COMPILER,"main.tex");
	do_argv(2,LATEX_COMPILER,"main.tex");
}
