/* $Id: queue.c,v 1.4 2012-11-19 15:23:37-08 - - $ */


#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

#define STUBPRINTF(...) fprintf (stderr, __VA_ARGS__);

static char *queue_tag = "struct queue";
static char *queuenode_tag = "struct queuenode";

typedef struct queuenode *queuenode_ref;

struct queuenode {
   char *tag;
   queue_item_t item;
   queuenode_ref link;
};

struct queue {
   char *tag;
   queuenode_ref front;
   queuenode_ref rear;
};

queue_ref new_queue (void) {
   queue_ref new = malloc (sizeof (struct queue));
   assert(new != NULL);
   new->tag = queue_tag;
   return new;
}

void free_queue (queue_ref queue) {
   assert (is_queue (queue));
   assert (isempty_queue (queue));
   memset (queue, 0, sizeof (struct queue));
   free (queue);
}

void insert_queue (queue_ref queue, queue_item_t item) {
   assert (is_queue (queue));
   queuenode_ref new = malloc (sizeof (struct queue));
   new->tag = queuenode_tag;
   new->item = item;
   new->link = NULL;
   if(queue->front == NULL){
        queue->front = new;
        queue->rear = queue->front;
   }else{
       queue->rear->link = new;
       queue->rear = queue->rear->link;
   }
}

queue_item_t remove_queue (queue_ref queue) {
   assert (is_queue (queue));
   assert (! isempty_queue (queue));
   queuenode_ref old = queue->front;
   queue_item_t temp = old->item;
   queue->front = queue->front->link;
   free(old);
   return temp;
}

bool isempty_queue (queue_ref queue) {
   assert (is_queue (queue));
   return queue->front == NULL;
}

bool is_queue (queue_ref queue) {
   return queue != NULL && queue->tag == queue_tag;
}

