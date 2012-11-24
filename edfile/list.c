// $Id: list.c,v 1.13 2012-11-14 21:36:52-08 - - $

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "debugf.h"
#include "list.h"

static char *list_tag = "struct list";
static char *listnode_tag = "struct listnode";

typedef struct listnode *listnode_ref;

struct list {
   //
   // INVARIANT:  Both head and last are NULL or neither are NULL.
   // If neither are null, then following listnode next links from
   // head will get to last, and prev links from last gets to head.
   //
   char *tag;
   listnode_ref head;
   listnode_ref curr;
   listnode_ref last;
};

struct listnode {
   char *tag;
   char *line;
   listnode_ref prev;
   listnode_ref next;
};

void debugdump_list (list_ref list) {
   listnode_ref itor = NULL;
   assert (is_list (list));
   fflush (NULL);
   fprintf (stderr,
            "\n[%p]->struct list {tag=[%p]->[%s];"
            " head=[%p]; curr=[%p]; last=[%p]; }\n",
            list, list->tag, list->tag,
            list->head, list->curr, list->last);
   for (itor = list->head; itor != NULL; itor = itor->next) {
      fprintf (stderr,
               "[%p]->struct listnode {tag=[%p]->[%s];"
               " line=[%p]=[%s]; prev=[%p]; next=[%p]; }\n",
               itor, itor->tag, itor->tag, itor->line, itor->line,
               itor->prev, itor->next);
   }
   fflush (NULL);
}


list_ref new_list (void) {
   //
   // Creates a new struct list.
   //
   list_ref list = malloc (sizeof (struct list));
   assert (list != NULL);
   list->tag = list_tag;
   list->head = NULL;
   list->curr = NULL;
   list->last = NULL;
   return list;
}

void free_list (list_ref list) {
   assert (is_list (list));
   assert (empty_list (list));
   memset (list, 0, sizeof (struct list));
   free (list);
}

bool setmove_list (list_ref list, list_move move) {
   assert (is_list (list));
   switch (move) {
      case MOVE_HEAD:
           STUBPRINTF ("MOVE_HEAD: list=[%p]\n", list);
           break;
      case MOVE_PREV:
           STUBPRINTF ("MOVE_PREV: list=[%p]\n", list);
           break;
      case MOVE_NEXT:
           STUBPRINTF ("MOVE_NEXT: list=[%p]\n", list);
           break;
      case MOVE_LAST:
           STUBPRINTF ("MOVE_LAST: list=[%p]\n", list);
           break;
      default: assert (false);
   }
   return false;
}

char *viewcurr_list (list_ref list) {
   assert (is_list (list));
   STUBPRINTF ("list=[%p]\n", list);
   return NULL;
}


void insert_list (list_ref list, char *line) {
   assert (is_list (list));
   STUBPRINTF ("list=[%p], line=[%p]=%s\n", list, line, line);
}

void delete_list (list_ref list) {
   assert (is_list (list));
   assert (! empty_list (list));
   STUBPRINTF ("list=[%p]\n", list);
}

bool empty_list (list_ref list) {
   assert (is_list (list));
   return list->head == NULL;
}

bool is_list (list_ref list) {
   return list != NULL && list->tag == list_tag;
}

