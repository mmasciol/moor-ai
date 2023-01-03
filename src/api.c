// https://stackoverflow.com/questions/1398307/how-can-i-allocate-memory-and-return-it-via-a-pointer-parameter-to-the-calling

#include <stdio.h>
#include <stdlib.h>

#include "api.h"
#include "def.h"
#include "sys.h"

ERROR_CODE api_allocate_domain(Domain **d, char *msg)
{
  printf("--> Outside DLL!\n");
  *d = malloc(sizeof(Domain));
  return 0;
}

ERROR_CODE api_free_domain(Domain **d, char *msg)
{
  printf("--> Free Domain DLL!\n");
  if (*d) {
    checkpoint();
    free(*d);
  }
  return 0;
}
