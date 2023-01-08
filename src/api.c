// https://stackoverflow.com/questions/1398307/how-can-i-allocate-memory-and-return-it-via-a-pointer-parameter-to-the-calling

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "api.h"
#include "bstrlib.h"
#include "def.h"
#include "sys.h"
#include "yaml-c-wrap/api.h"

ERROR_CODE api_allocate_domain(void **d, char **msg)
{
  ERROR_CODE ierr = SAFE;
  *msg = NULL;

  *msg = (char *)malloc(1024 * sizeof(char));
  RESETERR();
  CHECKERRQ(VERBOSE, __func__);

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

  RESETERR();
  CHECKERRQ(VERBOSE, __func__);

  CHECKERRQ(VERBOSE, "Deallocated domain");
  CHECKERRQ(ERROR, "second domain");
  CHECKERRQ(FATAL, "another domain");

  if (*d) {
    free(*d);
  }
  return ierr;
CLEAN_UP:
  return FATAL;
}

ERROR_CODE api_read_yaml_file(void **d, char *fpath, char **msg)
{
  ERROR_CODE ierr = SAFE;
  bstring message = NULL;
  void *yaml = NULL;

  RESETERR();
  CHECKERRQ(VERBOSE, __func__);

  message = bformat("Reading *.yaml file <%s>", fpath);
  CHECKERRQ(INFO, message->data);
  bdestroy(message);

  yaml = yaml_open_file(fpath);
  yaml_close_file(yaml);

  return ierr;
CLEAN_UP:
  return FATAL;
}

ERROR_CODE api_flush_msg(char **msg)
{
  ERROR_CODE ierr = SAFE;

  RESETERR();
  CHECKERRQ(VERBOSE, __func__);

  if (*msg) {
    free(*msg);
    *msg = NULL;
  }
  return ierr;
CLEAN_UP:
  return FATAL;
}
