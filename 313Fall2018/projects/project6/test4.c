/*
 * File: test4.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "frac_heap.h"

int main()
{
  printf("\n******** TEST 4 *********\n");

  init_heap();

  /*Test large number of allocations*/
  fraction *f = NULL;
  del_frac(f);
  
  for(int i = 0; i<1000; i++){
     new_frac();
  }

  dump_heap();

  return 0;
}
