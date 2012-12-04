/* 
 * File:   l8stat.c
 * Author: Hai Vo
 *
 * Created on November 28, 2012, 2:29 PM
 */

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <libgen.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

char *Exec_Name;
int  Exit_Status = EXIT_SUCCESS;
struct tm *loctime;

int main(int argc, char** argv) {
    Exec_Name = basename (argv[0]);
    char buffer[60];
    int i;
    double datelimit = 15552000;
    struct stat statbuf;
    struct tm *tm;
    time_t curtime;
    double value;
    
    
    for (i = 1; i < argc; i++) {
       if (lstat(argv[i], &statbuf)) {
           perror(argv[i]);
           Exit_Status = EXIT_FAILURE;
       }else{
            char *pathname = argv[i];
            char linkname[PATH_MAX + 1];
            tm = localtime(&statbuf.st_mtime);
            time(&curtime);
            value = difftime(curtime, statbuf.st_mtime);
            printf("%f\n", value);
            if(value<0){
                value = -value;
            }
            printf("%o %6d", statbuf.st_mode, (int)statbuf.st_size);
            if(value>datelimit){
                strftime(buffer, 100, "%b %e %Y", tm);         
            }else{
                strftime(buffer, 100, "%b %e %R", tm);
            }
            printf(" %s %s ",buffer, argv[i]);
            if (S_ISLNK(statbuf.st_mode)){
                ssize_t retval = readlink (pathname, 
                        linkname, sizeof linkname);
                if (retval >= 0) {
                        linkname[retval < PATH_MAX + 1 
                                ? retval : PATH_MAX] = '\0';
                        printf ("%s -> %s", pathname, linkname);
                }
            }
            printf("\n");
        }
    }
    return (Exit_Status);
}

