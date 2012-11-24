// $Id: edfile.c,v 1.14 2012-11-14 21:35:53-08 - - $

#include <assert.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "debugf.h"
#include "list.h"

bool want_echo = false;

void badline (int stdincount, char *stdinline) {
   fflush (NULL);
   fprintf (stderr, "Bad input line %d: %s\n", stdincount, stdinline);
   fflush (NULL);
}

void editfile (list_ref list) {
   char stdinline[1024];
   int stdincount = 0;
   for(;; ++stdincount) {
      printf ("%s: ", Exec_Name);
      char *linepos = fgets (stdinline, sizeof stdinline, stdin);
      if (linepos == NULL) break;
      if (want_echo) printf ("%s", stdinline);
      linepos = strchr (stdinline, '\n');
      if (linepos == NULL || stdinline[0] == '\0') {
         badline (stdincount, stdinline);
      }else {
         *linepos = '\0';
         switch (stdinline[0]) {
            case '$': STUBPRINTF ("stdin[%d]: $\n", stdincount); break;
            case '*': STUBPRINTF ("stdin[%d]: *\n", stdincount); break;
            case '.': STUBPRINTF ("stdin[%d]: .\n", stdincount); break;
            case '0': STUBPRINTF ("stdin[%d]: 0\n", stdincount); break;
            case '<': STUBPRINTF ("stdin[%d]: <\n", stdincount); break;
            case '>': STUBPRINTF ("stdin[%d]: >\n", stdincount); break;
            case '@': debugdump_list (list); break;
            case 'a': STUBPRINTF ("stdin[%d]: a\n", stdincount); break;
            case 'd': STUBPRINTF ("stdin[%d]: d\n", stdincount); break;
            case 'i': STUBPRINTF ("stdin[%d]: i\n", stdincount); break;
            case 'r': STUBPRINTF ("stdin[%d]: r\n", stdincount); break;
            case 'w': STUBPRINTF ("stdin[%d]: w\n", stdincount); break;
            default : badline (stdincount, stdinline);
         }
      }
   }
}


void usage_exit() {
   fflush (NULL);
   fprintf (stderr, "Usage: %s filename\n", Exec_Name);
   fflush (NULL);
   exit (EXIT_FAILURE);
}

int main (int argc, char **argv) {
   Exec_Name = basename (argv[0]);
   if (argc != 2) usage_exit();
   want_echo = ! (isatty (fileno (stdin)) && isatty (fileno (stdout)));
   list_ref list = new_list();
   editfile (list);
   free_list (list); list = NULL;
   return Exit_Status;
}
