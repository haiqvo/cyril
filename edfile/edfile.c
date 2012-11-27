// $Id: edfile.c,v 1.14 2012-11-14 21:35:53-08 - - $

#include <assert.h>
#include <ctype.h>
#include <errno.h>
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

void putFileinList(list_ref list, FILE *input, 
   char *filename, int after){
   char buffer[1024];
   int linenr = 1;
   for (; ; ++linenr) {
      char *linepos = fgets (buffer, sizeof buffer, input);
      if (linepos == NULL) break;
      linepos = strchr (buffer, '\n');
      if (linepos == NULL) {
         fflush (NULL);
         fprintf (stderr, "%s: %s[%d]: unterminated line\n",
                  Exec_Name, filename, linenr);
         fflush (NULL);
         Exit_Status = EXIT_FAILURE;
      }else {
         *linepos = '\0';
      }
      linepos = strdup (buffer);
      assert (linepos != NULL);
      if(after == 1){
        insert_list (list, linepos);
      }else{
        insertAfter(list, linepos, last);
      }
   }
   if(after == 1){
          printf("%s: %d lines read from %s.\n", 
                  Exec_Name, counter(list, last), filename);
   }else{
       printf("%s: %d lines read from %s.\n", 
                  Exec_Name, linenr-1, filename);
   }
}

void putfilelist (list_ref list, char *filename, int after) {
    FILE *input;
   if(after == 2){
        input = fopen (filename, "w");
   }else{
        input = fopen (filename, "r");
   }
   if (input == NULL) {
      fflush (NULL);
      fprintf (stderr, "%s: %s: %s\n",
               Exec_Name, filename, strerror (errno));
      fflush (NULL);
      Exit_Status  = EXIT_FAILURE;
   }else {
      if(after == 2){
        writeFile(list, input);
      }else{
        putFileinList(list, input, filename, after);
      }
      fclose (input);
   }
}


void editfile (list_ref list) {
   char stdinline[1024];
   int stdincount = 0;
   for(;; ++stdincount) {
      printf ("%s: ", Exec_Name);
      char *linepos = fgets (stdinline, sizeof stdinline, stdin);
      if(isspace(stdinline[0]) != 0){
          continue;
      }
      if (linepos == NULL) break;
      if (want_echo) printf ("%s", stdinline);
      linepos = strchr (stdinline, '\n');
      if (linepos == NULL || stdinline[0] == '\0') {
         badline (stdincount, stdinline);
      }else {
         *linepos = '\0';
         switch (stdinline[0]) {
            case '$': setmove_list (list, MOVE_LAST); break;
            case '*': print_list(list); break;
            case '.': printf("%6d: %s\n",counter(list, curr), 
                    viewcurr_list (list)); break;
            case '0': setmove_list (list, MOVE_HEAD); break;
            case '<': setmove_list (list, MOVE_PREV); break;
            case '>': setmove_list (list, MOVE_NEXT); break;
            case '@': debugdump_list (list); break;
            case 'a': insertAfter(list, stdinline+1, curr); break;
            case 'd': delete_list (list); break;
            case 'i': insertBefore(list, stdinline+1); break;
            case 'r': putfilelist (list, stdinline+1, 0); break;
            case 'w': putfilelist (list, stdinline+1, 2); break;
            case '#': break;
            default : badline (stdincount, stdinline);
         }
      }
   }
   printf (" ^D\n");
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
   if(argc ==2){
        for (int argi = 1; argi < argc; ++argi) {
                putfilelist (list, argv[argi], 1);
        }
        editfile (list);
        free_list (list); list = NULL;
   }
   return Exit_Status;
}
