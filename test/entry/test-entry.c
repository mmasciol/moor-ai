#include <assert.h>
#include <stdio.h>

#include "api.h"

void yaml_file_read_failure();
void yaml_file_read_success();

#define TEST()                                                                 \
  printf("\n\n--------------------\n");                                        \
  printf("[TEST   ]   %s\n", __func__);                                        \
  printf("--------------------\n");

#define CHECKERR(code, s)                                                      \
  if (code && s)                                                               \
    printf("%s", s);

int main()
{
  yaml_file_read_failure();
  yaml_file_read_success();

  return 0;
}

void yaml_file_read_failure()
{
  TEST();
  void *domain = NULL;
  char *msg = NULL;
  int err = -9999;

  err = api_allocate_domain(&domain, &msg);
  assert(err == 2);
  CHECKERR(err, msg);

  err = api_read_yaml_file(&domain, "./does-not-exist.yaml", &msg);
  assert(err == 6);
  CHECKERR(err, msg);

  err = api_free_domain(&domain, &msg);
  assert(err == 2);
  CHECKERR(err, msg);

  err = api_flush_msg(&msg);
  assert(err == 2);
  CHECKERR(err, msg);

  return;
}

void yaml_file_read_success()
{
  TEST();
  void *domain = NULL;
  char *msg = NULL;
  int err = -9999;

  err = api_allocate_domain(&domain, &msg);
  assert(err == 2);
  CHECKERR(err, msg);

  err = api_read_yaml_file(&domain, "./test/test-1.yaml", &msg);
  assert(err == 2);
  CHECKERR(err, msg);

  err = api_free_domain(&domain, &msg);
  assert(err == 2);
  CHECKERR(err, msg);

  err = api_flush_msg(&msg);
  assert(err == 2);
  CHECKERR(err, msg);

  return;
}
