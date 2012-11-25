/*
 * mkmain.c
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

int select_tex(const struct dirent *entry)
{
   printf("%d\n",strcmp(entry->d_name,"main.tex"));
   if ((strcmp(entry->d_name, ".") == 0) || 
       (strcmp(entry->d_name, "..") == 0)||
       (entry->d_type!=DT_REG) || (check_extension(entry->d_name,".tex")==0)
                               || (strcmp(entry->d_name,"main.tex")==0)
                               || (strcmp(entry->d_name,"preamb.tex")==0))
     return (0);
   else
     return (1);
}

int select_dir(const struct dirent *entry)
{
   if ((strcmp(entry->d_name, ".") == 0) || 
       (strcmp(entry->d_name, "..") == 0)||
       (entry->d_type==DT_REG))
     return (0);
   else
     return (1);
}

/** mkmain():
 *  Creates the .tex for each .tex files. If the string is NULL, "." is replaced 
 */
int mkmain(char* path)
{
           struct dirent **namelist;
           int n, i=0;
           int mainv = 0;
           

           printf("\033[33m%s\033[0m\n", (path? path : "./"));;
           
           FILE *f = fopen("main.tex", "w+");
           if (!f) {
           	perror("opening main.tex");
           	exit(1);
           }

	   if (file_exists("preamb.tex",NULL,NULL,NULL)) {
	   	mainv = 1;
	   	fprintf(f,"\\input{preamb}\n\\begin{document}\n");
	   }

           n = scandir( ".", &namelist, select_tex, alphasort);
           if (n < 0)
               perror("scandir (tex)");
           else {
               for (i=0; i<n; i++)  {
                   int filelen = strlen(namelist[i]->d_name);
                   namelist[i]->d_name[filelen-4]='\0';
                   if (path) {
                   	fprintf(f,"\\input{%s/%s}\n",path,namelist[i]->d_name);
                   } else 
                   	fprintf(f,"\\input{%s}\n",namelist[i]->d_name);
                   free(namelist[i]);
               }
               free(namelist);
           }
           
           i=0;
           n = scandir( ".", &namelist, select_dir, alphasort);
           if (n < 0)
               perror("scandir (dir)");
           else {
               for (i=0; i<n; i++) {
                int filelen = strlen(namelist[i]->d_name);
               	char nfile[filelen+10+(path? strlen(path) : 0)];
               	char nfileskip[filelen+strlen(SKIP_FOLDER)+(path? strlen(path)+1 : 1)];
               	
               	char *here = get_current_dir_name();
               	strcpy(nfile,namelist[i]->d_name);
               	strcpy(nfileskip,namelist[i]->d_name);
               	strcat(nfile,"/main.tex");
               	strcat(nfileskip,"/");
               	strcat(nfileskip,SKIP_FOLDER);
               	if ((IS_FILE(nfile))&&(!IS_FILE(nfileskip))) {
               	   char nfile4[strlen(namelist[i]->d_name)+(path? strlen(path)+1 : 0)];
               	   if (path) {
		       	   strcpy(nfile4,path);
		       	   if (nfile4[strlen(nfile4)-1]!='/') strcat(nfile4,"/");
		       	   strcat(nfile4,namelist[i]->d_name);
		   } else strcpy(nfile4,namelist[i]->d_name);
		   
               	   filelen = strlen(nfile);
               	   nfile[filelen-4]='\0';
               	   if (!path) {
                   	fprintf(f,"\\input{%s}\n",nfile);
                   	printf("2----------->\\input{%s}\n",nfile);
                   } else {
                   	fprintf(f,"\\input{%s/main}\n",nfile4);
                   	printf("1----------->\\input{%s/main}\n",nfile4);
                   }
                   nfile[filelen-4]='.';
                   printf("\033[32mInside: %s\033[0m\n", namelist[i]->d_name);
                   chdir(namelist[i]->d_name);
                   mkmain(nfile4);
                   chdir(here);
                   free(here);
                   free(namelist[i]);
                } else {
                   if (!(IS_FILE(nfileskip))) {
		           printf("unexistant file %s\n",nfile);
		           exit(1);
		   }
                }
               }
               free(namelist);
           }
           
           if (mainv) {
           	fprintf(f,"\\end{document}");
           }
           fclose(f);
           
           return 0;
}
