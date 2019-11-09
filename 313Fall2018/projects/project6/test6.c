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
  fraction *f[1000];
  
  for(int i = 0; i<1000; i++){
     f[i] = new_frac();
  }

  for(int i = 0; i<1000; i++){
     del_frac(f[i]);
  }

  dump_heap();

  return 0;
}
