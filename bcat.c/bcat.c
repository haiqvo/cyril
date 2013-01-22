// $Id: bcat.c,v 1.110 2012-11-01 21:18:53-07 - - $
// Hai Vo hqvo@ucsc.edu
//
// NAME
//    bcat - concatenate and display files
//
// SYNOPSIS
//    bcat [filename...]
//
// DESCRIPTION
//    The bcat utility reads each file in sequence and writes it
//    to stdout.  If any filename is given as the single character
//    "-", stdin is read at that point.  If no filenames are given
//    then stdin is read as the only file.
//

#include <errno.h>
#include <libgen.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *progname = NULL;          // Name of the program being run.
int exit_status = EXIT_SUCCESS; // Assume successful completion.

struct options {                // Structure to hold options.
   bool moretitles;             // Print titles in more-style
   bool numberlines;            // Output line numbers for each line.
   bool squeeze;                // Squeeze multiple empty lines.
};


//
// cat -
// Copy the contents of an already-opened file to stdout.
//

void catfile (FILE *input, char *filename, struct options *opts) {
   char buffer[4096];
   if(opts->moretitles){
      printf("\n");
      int i;
      for(i=0;i<64;i++){
         printf(":");
      }
      printf("\n");
      printf("%s\n",filename);
      for(i=0;i<64;i++){
         printf(":");
      }
      printf("\n\n");
   }
   int counter=0;
   int tracker=0;
   for (;;) {
      char *bufrc = fgets (buffer, sizeof buffer, input);
      if (bufrc == NULL) break;
      if(opts->squeeze && !opts->numberlines){
         if(strcmp(buffer,"\n")==0){
            tracker++;
         }else{
            tracker=0;
         }
         if(tracker>=2){           
            continue;
         }
      }
      if(opts->numberlines && opts->squeeze){
         if(strcmp(buffer, "\n")==0){
            tracker++;
            counter++;
         }else{
            counter++;
            tracker=0;
         }
         if(tracker>=2){
            continue;
         }
         printf("%6d  ", counter);
      }
      if(opts->numberlines && !opts->squeeze){
         counter++;
         printf("%6d  ", counter);
      }
      printf("%s", buffer);
   };
}

// scanoptions -
// Scan the options and initialize a struct options.
//

void scan_options (int argc, char **argv, struct options *opts) {
   memset (opts, 0, sizeof (struct options));
   opterr = false;
   for (;;) {
      int opt = getopt (argc, argv, "mns");
      if (opt == EOF) break;
      switch (opt) {
         case 'm':
            opts->moretitles = true;
            break;
         case 'n':
            opts->numberlines = true;
            break;
         case 's':
            opts->squeeze = true;
            break;
         default : 
            fflush (NULL);
            fprintf (stderr, "%s: -%c: invalid option\n",
                     progname, optopt);
            fflush (NULL);
            exit_status = EXIT_FAILURE;
       }
   }
}


//
// main -
// Loop over files, if any, and cat each of them to stdout.
// Print error messages if appropriate.
//

int main (int argc, char **argv) {
   exit_status = EXIT_SUCCESS;
   progname = basename (argv[0]);
   struct options opts;
   scan_options (argc, argv, &opts);
   if (optind == argc) {
      catfile (stdin, "-", &opts);
   }else{
      for (int argi = optind; argi < argc; ++argi) {
         char *filename = argv[argi];
         if (strcmp (filename, "-") == 0) {
            catfile (stdin, "-", &opts);
         }else{
            FILE *input = fopen (filename, "r");
            if (input == NULL) {
               fflush (NULL);
               fprintf (stderr, "%s: %s: %s\n", progname,
                        argv[argi], strerror (errno));
               fflush (NULL);
               exit_status = EXIT_FAILURE;
            }else{
               catfile (input, filename, &opts);
               fclose (input);
            };
         };
      };
   };
   return exit_status;
}

