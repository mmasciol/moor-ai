#include <stdio.h>

#include "api.h"

#define CHECKERR(code, s)                                                      \
  if (code && s)                                                               \
    printf("%s", s);

int main()
{
  void *domain = NULL;
  char *msg = NULL;
  int err = -9999;

  err = api_allocate_domain(&domain, &msg);
  CHECKERR(err, msg);

  err = api_read_yaml_file(&domain, "./test/test-1.yaml", &msg);
  CHECKERR(err, msg);

  err = api_free_domain(&domain, &msg);
  CHECKERR(err, msg);

  err = api_flush_msg(&msg);
  CHECKERR(err, msg);

  return 0;
}
