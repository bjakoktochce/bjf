/* 
 * Copyright (c) 2017, 2018 Bartosz Jakoktochce, grypsy@gmail.com
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
#include <limits.h>

#include "version.h"

/*
 * Declaration of functions
 */

void usage(void);

/*
 * Main part of the program
 */

int main(int argc, char **argv) 
{
	struct stat fs;				// file stats
	struct passwd *pwd;			// passwd struct
	struct group *grp;			// group struct
	struct mode_t *mode;		// file permissions and mode
	char buf[PATH_MAX + 1];		// buffer for real pathname

	if (argc < 2) {									// if no arguments are passed
		usage();									// show only usage message
		return 0;									// and exit with code 0
	}
	else {

		if (stat64(argv[1], &fs) == -1) {			// Check if the stat64() function returns error (-1)
			perror(argv[1]);						// print error to stdout
			return EXIT_FAILURE;					// and exit program with code 0
		}
      		else {
			printf("	-- detailed file information --\n");
			printf("file: %s\n", argv[1]);										// print filename passed as argument
			printf("path: %s\n", realpath(argv[1], buf));						// get and print real path of the file
			printf("size: %ld bytes\n", fs.st_size);							// size in bytes
			printf("block size: %ld\n", fs.st_blksize);							// size of one block
			printf("number of blocks allocated: %ld\n", fs.st_blocks);			// number of blocks
			printf("inode number: %ld\n", fs.st_ino);							// inode number
			printf("number of hard links: %ld\n", fs.st_nlink);					// number of hard links pointing to file
			printf("device id: %i (major) %i (minor)\n", major(fs.st_dev), minor(fs.st_dev));
			printf("last accessed: %s", ctime(&fs.st_atime));					// last access
			printf("last modified: %s", ctime(&fs.st_mtime));					// last modify
			printf("last changed:  %s", ctime(&fs.st_ctime));					// last change
			printf("permissions: %o\n", fs.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));		// permissions
	

			// Print informations about the owner

			pwd=getpwuid(fs.st_uid);
			grp=getgrgid(fs.st_gid);
			printf("\n	-- owner information --\n");
			printf("UID: %d (%s), GID: %d (%s)\n", fs.st_uid, pwd->pw_name, pwd->pw_gid, grp->gr_name); 	// uid, gid, username and group name
			printf("GEKOS field: %s\n", pwd->pw_gecos);						// gekos field
			printf("home: %s\n", pwd->pw_dir);								// home directory
			printf("shell: %s\n", pwd->pw_shell);							// shell
	
		}

		// It's time to finish the program with exit code 0

		return 0;
	}
}

/*
 * Shows usage of the program
 */

void usage(void)
{
	printf("bjf %s shows detailed information about the specified file on the system.\n", VERSION);
	printf("usage: bjf <filename>\n");
}
