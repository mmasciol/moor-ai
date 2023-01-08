#include <stdio.h>

#include "api.h"

#define CHECKERR(code, s)                                                      \
  if (code)                                                                    \
    printf("%s", s);

int main()
{
  void *domain = NULL;
  char *msg = NULL;
  int err = -9999;

  err = api_allocate_domain(&domain, &msg);
  // CHECKERR(1, msg);

  err = api_free_domain(&domain, &msg);
  // CHECKERR(1, msg);

  err = api_flush_msg(&msg);
  // CHECKERR(1, msg);

  return 0;
}
