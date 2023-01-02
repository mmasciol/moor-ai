// https://stackoverflow.com/questions/1398307/how-can-i-allocate-memory-and-return-it-via-a-pointer-parameter-to-the-calling

#include <stdio.h>

int api_hook() {
  printf("--> Inside DLL!\n");
  return 0;
}

int api_allocate_domain(struct Domain **d) {
  printf("--> Outside DLL!\n");
  return 0;
}
