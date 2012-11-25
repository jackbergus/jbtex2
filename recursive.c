/*
 * recursive.c
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

/**  recursiveDelete():
 *  Effettua l'eliminazione ricorsiva degli elementi all'interno della directory
 *  @param dirname:	Percorso della cartella da svuotare ricorsivamente
 */
void recursiveDelete(char* dirname) {

  char* tmp;
  DIR *direct;
  struct dirent *dir;

  char *abs_filename;
  asprintf(&tmp, "%s", dirname);
  
  while ((tmp[strlen(tmp)-1]=='/')&&(strlen(tmp)))
  	tmp[strlen(tmp)-1] = '\0';
  if (!strlen(tmp))
  	return;
   
  printf("%s",tmp); 

  direct = opendir (tmp);
  if (direct) {
      while (dir = readdir (direct)) {
        struct stat stt;

        asprintf(&abs_filename, "%s/%s", tmp, dir->d_name);
        stat(abs_filename, &stt);
        

        if(S_ISDIR(stt.st_mode)) {
          if(strcmp(dir->d_name, ".") && 
             strcmp(dir->d_name, "..")) {
             printf("Folder %s....\n", abs_filename); 
            recursiveDelete(abs_filename);
          }
        } else {
        	  printf("Deleting %s....\n", abs_filename);
                  unlink(abs_filename);
        }
        
        free(abs_filename);
        
      }
      closedir(direct);
      remove(tmp);
  }
  
  free(tmp);

}

/** check_extension():
 *  Checks the file extension 
 */
char check_extension(char* file, char* end) {
	if (strlen(end)>strlen(file)) return (char)0;
	char toret;
	int len = strlen(file)-strlen(end);
	toret = (char)(strcmp(&file[len],end)==0);
	if (toret) printf("%d %s %s\n", (int)toret, file, end);
	return toret;
}

/** file_exist():
 *  Checks the file existance
 *  @param filename	Given File name
 *  @param time	   	Returns the creation time
 *  @param retbuf	Eventually copies the file's stat
 *  @param pfd		Eventually returns the file's File Descriptor, otherwise
 *			the fd will be closed
 */
char file_exists(char * filename, unsigned int *time, struct stat *retbuf, int *pfd)
{    
    int fd    = open(filename, O_RDWR);
    char test = (char)0;

    if ((filename)&&(fd>-1)) {
    	    
	struct stat buf;
	char val;
	
	fstat(fd, &buf); 
	if (time)
	   *time = (unsigned int)buf.st_ctime;

	    	    
	if (S_ISDIR(buf.st_mode)) test=(char)2;
	else test=(char)1; 
	    	    
	if (!pfd) close(fd); else *pfd = fd;
	if (retbuf) *retbuf = buf;
	
	return test;   

    } 
    
    return (char)0;
}

/** folder_empty():
 *  Checks if the given folder is empty 
 */
char folder_empty(char *dirname) 
{
	int n = 0;
	DIR *dir = opendir(dirname);
  
	/* If the folder doesn't exists */
	if (!(dir = opendir(dirname)))
		return (char)-1;
  
	/* Checks for . and .. */
	while (readdir(dir)) {
		if(++n > 2) break;
	}
	closedir(dir);
  
	/* If there are only . and .., then return false */
	return ((char)(n <= 2)); 
}

/** runcommand():
 *  Does the fork, executes the command, and waits for the child
 */
void runcommand(char* command[]) {
	pid_t child; 
	int retnum;  
	if ((child=fork())>0) {
		  waitpid(child, &retnum, 0);
	} else {
		execv(command[0],command);
		exit(0);
	}
	return;
}


/** do_argv():
 *  given a parametric string, returns an allocated array, where all the
 *  arguments are stored */
void do_argv(int n, ...)
{
    va_list ap;
    if (n>=ARG_MAX) n = ARG_MAX;
    char** args=(char**)malloc(sizeof(char**)*n);
    int i = 0, j= 0;
 
    va_start(ap, n);
    for (; n; n--)
        args[i++] = va_arg(ap, char*);
    va_end(ap);
    args[i] = NULL;
    
    runcommand(args);
    
    free(args);
    return;
}


