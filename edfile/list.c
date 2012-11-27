// $Id: list.c,v 1.13 2012-11-14 21:36:52-08 - - $

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
   while(list->head != NULL){
       list->curr = list->head;
       free(list->curr->line);
       free(list->curr);
       list->head = list->head->next;
   }
   assert (empty_list (list));
   memset (list, 0, sizeof (struct list));
   free (list);
}

bool setmove_list (list_ref list, list_move move) {
   assert (is_list (list));
   switch (move) {
      case MOVE_HEAD:
           list->curr = list->head;
           printf("%6d: %s\n",counter(list, curr), list->curr->line);
           break;
      case MOVE_PREV:
           if(list->curr->prev == NULL){
               list->curr = list->curr;
           }else{
               list->curr = list->curr->prev;
           }
           printf("%6d: %s\n",counter(list, curr), list->curr->line);
           break;
      case MOVE_NEXT:
           if(list->curr->next == NULL){
               list->curr = list->curr;
           }else{
               list->curr = list->curr->next;
           }
           printf("%6d: %s\n",counter(list, curr), list->curr->line);
           break;
      case MOVE_LAST:
           list->curr = list->last;
           printf("%6d: %s\n",counter(list, curr), list->curr->line);
           break;
      default: assert (false);
   }
   return false;
}

int counter (list_ref list, list_type type){
    assert(is_list (list));
    int count = 0;
    listnode_ref temp = list->head;
    switch(type){
        case curr:
            while(temp != list->curr){
                count++;
                temp = temp->next;
            } 
            break;
        case last:
            while(temp != NULL){
                count++;
                temp = temp->next;
            }
            break;
        default: break;
    }
    return count;
}

char *viewcurr_list (list_ref list) {
   assert (is_list (list));
   return list->curr->line;
}


void insert_list (list_ref list, char *line) {
   assert (is_list (list));
   listnode_ref new = malloc (sizeof (struct list));
   new->tag = listnode_tag;
   new->line = line;
   new->next = NULL;
   new->prev = NULL;
   if(list->head == NULL){
       list->head = new;
       list->last = new;
       list->curr = new;
   }else{
       list->last->next = new;
       new->next = NULL;
       new->prev = list->last;
       list->last = new;
   }
   list->curr = list->last;
}

void insertAfter(list_ref list, char *line, list_type type){
    assert(is_list(list));
    listnode_ref new = malloc(sizeof (struct list));
    new->tag = listnode_tag;
    new->line = strdup(line);
    if(list->curr->next == NULL){
        new->next = NULL;
        list->curr->next = new;
        new->prev = list->last;
        list->last = new;
    }else{
        new->prev = list->curr;
        new->next = list->curr->next ; 
        list->curr->next->prev = new;
        list->curr->next = new;
    }
    list->curr = list->curr->next;
    if(type == curr)
    printf("%6d: %s\n",counter(list, curr), list->curr->line);
}

void insertBefore(list_ref list, char *line){
    assert(is_list(list));
    listnode_ref new = malloc(sizeof (struct list));
    new->tag = listnode_tag;
    new->line = strdup(line);
    if(list->curr->prev == NULL){
        new->prev = NULL;
        list->curr->prev = new;
        new->next = list->head;
        list->head = new;
    }else{
        new->next = list->curr;
        new->prev = list->curr->prev;
        list->curr->prev->next = new;
        list->curr->prev = new;
    }
    list->curr = list->curr->prev;
    printf("%6d: %s\n",counter(list, curr), list->curr->line);
}

void print_list(list_ref list){
    listnode_ref temp = list->head;
    int counter = 0;
    while(temp != NULL){
       printf("%6d: %s\n",counter, temp->line);
       counter++;
       temp = temp->next;
    }
}

void delete_list (list_ref list) {
   assert (is_list (list));
   assert (! empty_list (list));
   if(list->curr->prev == NULL){
       list->head = list->curr->next;
   }else{
       list->curr->prev->next = list->curr->next;
   }
   if(list->curr->next == NULL){
       list->last = list->curr->prev;
   }else{
       list->curr->next->prev = list->curr->prev;
   }
   free (list->curr->line);  
   free (list->curr);
   if(list->curr->next != NULL){
       list->curr = list->curr->next;
       printf("%6d: %s\n",counter(list, curr), list->curr->line);
   }
   else if(list->curr->prev != NULL){ 
       list->curr = list->curr->prev;
       printf("%6d: %s\n",counter(list, curr), list->curr->line);
   }else{
       printf("the list is blank.\n");
   }
}

void writeFile(list_ref list, FILE *filename){
    listnode_ref temp = list->head;
    while(temp != NULL){
        fprintf(filename,"%s\n",temp->line);
        temp = temp->next;
    }
    list->curr = list->last;
}

bool empty_list (list_ref list) {
   assert (is_list (list));
   return list->head == NULL;
}

bool is_list (list_ref list) {
   return list != NULL && list->tag == list_tag;
}

