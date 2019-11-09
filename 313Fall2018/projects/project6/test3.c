/*
 * File: test3.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "frac_heap.h"

int main()
{
  printf("\n******** TEST 3 *********\n");

  init_heap();

  /* Test passing null pointed fraction to delete */
  /* Should print error */
  fraction *f = NULL;
  del_frac(f);

  f = new_frac();
  fraction *f2 = new_frac();

  del_frac(f);
  del_frac(f2);

  dump_heap();

  return 0;
}
