/*
 * File: test5.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "frac_heap.h"

int main()
{
  printf("\n******** TEST 4 *********\n");

  init_heap();

  /*Test large number of allocations followed by deletions*/
  fraction *f = NULL;
  del_frac(f);
  
  for(int i = 0; i<1000; i++){
     f = new_frac();
     del_frac(f);
  }

  dump_heap();

  return 0;
}
