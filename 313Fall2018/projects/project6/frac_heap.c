#include "frac_heap.h"
#include <stdlib.h>
#include <stdio.h>

#define MALLOC 10


union fraction_block_u {
  union fraction_block_u *next;
  fraction frac;
};

typedef union fraction_block_u fraction_block;


static fraction_block *head;

/* dump_head  */
/* dumps heap */
void dump_heap() {

  char header[] = "**** BEGIN HEAP DUMP ****";
  char footer[] = "**** END HEAP DUMP ****";

  printf("%s\n\n", header);

  fraction_block *ptr = head;
  while (ptr != NULL) {
    printf("    %p\n", ptr);
    ptr = ptr->next;
  }

  printf("%s\n\n", footer);
}

/* init_heap */
/* instantiates the structure */
void init_heap() {

  head = NULL;

}

/* new_frac */
/* creates a new frac and inserts it into the list */
fraction *new_frac() {

  fraction_block *temp;

  if (head == NULL) {
    /* calaculates if there is more memory */
    head = malloc(sizeof(fraction_block) * MALLOC);
     
    if (head == NULL) {
      printf("Error: No more memory to be allocated!\n");
      exit(1);
    }

    printf("called malloc(%d): return %p\n\n", 
	   sizeof(fraction_block) * MALLOC, head);

    int i;
    for (i = 0; i < MALLOC; i++) {
      if (i == MALLOC - 1) {
	    head[i].next = NULL;
      }
      else {
	    head[i].next = &head[i + 1];
      }
    }
  }

  temp = head;
  head = head->next;
  return &(temp->frac);
}

/* del_frac */
/* deletes a fraction from the list */
void del_frac(fraction *frac) {

  if (frac == NULL) {
    printf("Error: del_frac() called on NULL pointer.\n");
  }
  else {
    fraction_block *temp;
    temp = (fraction_block *) frac;
  
    temp->next = head;
    head = temp;
  }
}

