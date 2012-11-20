// $Id: nsort.c,v 1.1 2011-04-29 19:46:42-07 - - $

#include <assert.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node *node_ref;
struct node {
    double item;
    node_ref link;
};

int main (int argc, char **argv) {
   double num;
   char *progname = basename (argv[0]);
   node_ref head = NULL;
   int debug=0;
   char *option = argv[1];
   int EXIT_STATUS = EXIT_SUCCESS;
   if (argc > 1){
        if(option[1] == 'd') debug = 1;
   }
   for (;;) {
      int rc = scanf ("%lg", &num);
      if(rc == EOF){
          break;
      }
      if(rc != 1){
          EXIT_STATUS = EXIT_FAILURE;
          fprintf (stderr, "%s: inputs is "
                  "not a number\n", progname);
          break;
      }
      node_ref new = malloc (sizeof (struct node));
      assert (new != NULL);
      node_ref curr = head;
      node_ref prev = NULL;
      while(curr!=NULL){
          if(curr->item > num) break;
          prev = curr;
          curr = curr->link;
      }
      new->item = num;
      new->link = curr;
      if(prev == NULL)head = new;
      else prev->link = new;
   }
   node_ref curr;
   if(EXIT_STATUS != 1){
        if(debug == 1){
            for (curr = head; curr != NULL; curr = curr->link){
                printf ("%p -> struct node {item= %.15g, link= %p}\n",
                 (void*) curr, curr->item, (void*) curr->link);
            }
        }else{
            for (curr = head; curr != NULL; curr = curr->link){
                printf ("%24.15g\n", curr->item);
            }
        }
   }
   while (head != NULL) {
      node_ref old = head;
      head = head->link;
      free (old);
   }
   return EXIT_STATUS;
}
