// https://stackoverflow.com/questions/1398307/how-can-i-allocate-memory-and-return-it-via-a-pointer-parameter-to-the-calling

#include <stdio.h>
#include <stdlib.h>

#include "def.h"

int api_hook() {
  printf("--> Inside DLL!\n");
  return 0;
}

int api_allocate_domain(Domain **d) {
  printf("--> Outside DLL!\n");
  *d = malloc(sizeof(Domain));
  return 0;
}

int api_free_domain(Domain **d) {
  printf("--> Free Domain DLL!\n");
  *d = malloc(sizeof(Domain));
  return 0;
}
