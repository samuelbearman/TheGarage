/*
 * File: test2.c
*/

#include <stdio.h>
#include <stdlib.h>
#include "frac_heap.h"

int main()
{
  printf("\n******** TEST 2 *********\n");

  init_heap();

  /* Allocate and delete in mixed order to test segmentation faults */
  fraction *fracs[17];

  int i;
  for (i = 0; i < 17; i++)
  {
    fracs[i] = new_frac();
  }

  /* Should show 3 free addresses in the heap */
  dump_heap();

  del_frac(fracs[10]);
  del_frac(fracs[3]);
  del_frac(fracs[6]);

  dump_heap();

  return 0;
}
