/*
 * mkjbt.c
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

static int mkjbt_step(const char *fpath, const struct stat *sb, int tflag,
		 struct FTW *ftwbuf)
{
	int flag = 0;

	if (IS_FILE("skip_this")) 
			flag = flag | FTW_SKIP_SUBTREE | FTW_SKIP_SIBLINGS;
	else if (tflag == FTW_F) {
		if (check_extension(fpath + ftwbuf->base,IS_JBT)) {
			printf("\033[31m%s %s\033[0m\n", fpath, IS_JBT);
			makejbt(fpath + ftwbuf->base);
		}
		flag = flag | FTW_CONTINUE;
	}
	
	return flag;
}

void mkjbt() {
	int flags = FTW_PHYS | FTW_ACTIONRETVAL | FTW_CHDIR;
	if (nftw(".", mkjbt_step, 20, flags)== -1) {
 		perror("nftw");
		exit(EXIT_FAILURE);
	}
}

