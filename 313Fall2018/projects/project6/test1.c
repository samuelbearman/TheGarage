/*
 * File: test1.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "frac_heap.h"

int main()
{
  printf("\n******** TEST 1 *********\n\n");

  init_heap();

  dump_heap();

  fraction *fracs[10];

  /* Assign all 10 from allocation chunk */
  int i;
  for (i = 0; i < 10; i++)
  {
    fracs[i] = new_frac();
  }

  /* Show no free unions */
  dump_heap();

  del_frac(fracs[9]);
  
  /* Should be one address free */
  dump_heap();

  /* Assign two more to fill one free and create new allocation chunk */
  fracs[9] = new_frac();
  fraction *f = new_frac();

  dump_heap();

  del_frac(f);

  return 0;
}
