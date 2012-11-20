// $Id: lsort.c,v 1.1 2011-04-29 19:46:42-07 - - $

#include <assert.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char *cstring;
typedef struct node *node_ref;
struct node {
    cstring item;
    node_ref link;
};

int main (int argc, char **argv) {
   char *progname = basename (argv[0]);
   node_ref head = NULL;
   int debug=0;
   char buffer[72];
   char *option = argv[1];
   int EXIT_STATUS = EXIT_SUCCESS;
   if (argc > 1){
        if(option[1] == 'd') debug = 1;
   }
   int linenr;
   for (linenr = 1; ; ++linenr) {
      char *gotline = fgets (buffer, sizeof buffer, stdin);
      if (gotline == NULL) break;
      char *nlpos = strchr(buffer, '\n');
      if (nlpos != NULL) {
         *nlpos = '\0';
      }else {
         fprintf (stderr, "%s: %d: unterminated line because"
                 " is too long: %s\n",
                  progname, linenr, buffer);
         EXIT_STATUS = EXIT_FAILURE;
      };
      node_ref new = malloc (sizeof (struct node));
      assert (new != NULL);
      node_ref curr = head;
      node_ref prev = NULL;
      char *word = strdup (buffer);
      while(curr!=NULL){
          if(strcmp (curr->item, word)>0) break;
          prev = curr;
          curr = curr->link;
      }
      new->item = strdup (buffer);
      new->link = curr;
      if(prev == NULL)head = new;
      else prev->link = new;
      free(word);
   }
   node_ref curr;
   if(EXIT_STATUS != 1){
      if(debug == 1){
           for (curr = head; curr != NULL; curr = curr->link){
                printf ("%p -> struct node {item= %s, link= %p}\n",
                     (void*) curr, curr->item, (void*) curr->link);
                }
      }else{
           for (curr = head; curr != NULL; curr = curr->link){
                printf ("%s\n", curr->item);
           }
      }
   }
   while (head != NULL) {
      node_ref old = head;
      head = head->link;
      free(old->item);
      free (old);
   }
   return EXIT_STATUS;
}
