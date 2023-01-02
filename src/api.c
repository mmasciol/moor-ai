#include <stdio.h>

int api_allocate() {
  printf("--> Inside DLL!\n");
  return 0;
}

int api_test() {
  printf("--> Outside DLL!\n");
  return 1;
}
