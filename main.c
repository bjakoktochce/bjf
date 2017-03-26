/* 
 * Copyright (c) 2017, Bartosz Jakoktochce, grypsy@gmail.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    This product includes software developed by the <organization>.
 * 4. Neither the name of the <organization> nor the
 *    names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY <COPYRIGHT HOLDER> ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
 
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <pwd.h>
#include <time.h>
#include <stdlib.h>
#include <grp.h>
#include <errno.h>

#include "version.h"

void 
usage(void);

/*
 * Main part of the program
 *
 */

int 
main(int argc, char **argv) 
{
	struct stat fs;		// file stats
	struct passwd *pwd;	// passwd struct
	struct group *grp;	// group struct
	struct mode_t *mode;

	if (argc < 2) {									// if no arguments are passed
		printf("bjf %s shows detailed information about the specified file on the system.\n", VERSION);
        	printf("usage: bjf <filename>\n");									 
		//usage();								// show only usage message
		return 0;								// and exit with code 0
	}
	else {

		if (stat64(argv[1], &fs) == -1) {					// Check if the stat64() function return error (-1)
			printf("bjf: %s: No such file or directory\n", argv[1]);			// write information to stdout
			//fprintf(stderr, "%s\n", strerror(errno));			// 
			return 0;							// and exit program with code 0
		}
      		else {
			printf("	-- detailed file information --\n");
			printf("file: %s\n", argv[1]);
			//printf("path: %s\n", getwd(argv[1]));
			printf("size: %ld bytes\n", fs.st_size);
			printf("block size: %ld\n", fs.st_blksize);
			printf("number of blocks allocated: %ld\n", fs.st_blocks);
			printf("inode number: %ld\n", fs.st_ino);
			printf("number of hard links: %ld\n", fs.st_nlink);
			printf("device id: %ld\n", fs.st_dev);
			printf("last accessed: %s", ctime(&fs.st_atime));	
			printf("last modified: %s", ctime(&fs.st_mtime));
			printf("last changed:  %s", ctime(&fs.st_ctime));
	
			pwd=getpwuid(fs.st_uid);
			grp=getgrgid(fs.st_gid);
			printf("\n	-- owner information --\n");
			printf("UID: %d (%s), GID: %d (%s)\n", fs.st_uid, pwd->pw_name, pwd->pw_gid, grp->gr_name);
			printf("GEKOS field: %s\n", pwd->pw_gecos);
			printf("home: %s\n", pwd->pw_dir);
			printf("shell: %s\n", pwd->pw_shell);
	
		}

		return 0;
	}
}

/*
 * Shows usage of the program
 */

void 
usage(void)
{
	printf("bjf %s shows detailed information about the specified file on the system.\n", VERSION);
        printf("usage: bjf <filename>\n");
}
