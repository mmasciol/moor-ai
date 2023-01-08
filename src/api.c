// https://stackoverflow.com/questions/1398307/how-can-i-allocate-memory-and-return-it-via-a-pointer-parameter-to-the-calling

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "api.h"
#include "def.h"
#include "sys.h"

ERROR_CODE api_allocate_domain(void **d, char **msg)
{
  ERROR_CODE ierr = SAFE;
  *msg = NULL;
  *msg = (char *)malloc(1024 * sizeof(char));
  *msg[0] = '\0';

  *d = malloc(sizeof(Domain));

  // if (*d) {
  //   CHECKERRQ(VERBOSE, "Allocated Domain");
  // }
  return ierr;
CLEAN_UP:
  return FATAL;
}

ERROR_CODE api_free_domain(void **d, char **msg)
{
  ERROR_CODE ierr = SAFE;

  CHECKERRQ(VERBOSE, "Deallocated domain");
  CHECKERRQ(ERROR, "second domain");
  CHECKERRQ(FATAL, "another domain");

  if (*d) {
    free(*d);
  }
  return SAFE;
CLEAN_UP:
  return FATAL;
}

ERROR_CODE api_flush_msg(char **msg)
{
  if (*msg) {
    free(*msg);
    *msg = NULL;
  }
  return SAFE;
CLEAN_UP:
  return FATAL;
}
