// https://stackoverflow.com/questions/1398307/how-can-i-allocate-memory-and-return-it-via-a-pointer-parameter-to-the-calling

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "api.h"
#include "bstrlib.h"
#include "def.h"
#include "parse.h"
#include "sys.h"
#include "yaml.h"

ERROR_CODE api_allocate_domain(void **d, char **msg)
{
  ERROR_CODE ierr = SAFE;
  *msg = NULL;

  *msg = (char *)malloc(1024 * sizeof(char));
  RESETERR();
  EMITERRQ(STACK, __func__);

  *d = malloc(sizeof(Domain));

  // if (*d) {
  //   EMITERRQ(VERBOSE, "Allocated Domain");
  // }

  return ierr;
CLEAN_UP:
  return FATAL;
}

ERROR_CODE api_free_domain(void **d, char **msg)
{
  ERROR_CODE ierr = SAFE;

  RESETERR();
  EMITERRQ(STACK, __func__);

  if (*d) {
    EMITERRQ(VERBOSE, "Deallocated domain");
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

  RESETERR();
  EMITERRQ(STACK, __func__);

  message = bformat("Reading *.yaml file <%s>", fpath);
  EMITERRQ(INFO, (const char*)message->data);
  bdestroy(message);

  ierr = parse_yaml(*d, fpath, msg); CHECKERRQ(FATAL, "*.yaml parsing failed.");

  return ierr;
CLEAN_UP:
  return FATAL;
}

ERROR_CODE api_flush_msg(char **msg)
{
  ERROR_CODE ierr = SAFE;

  RESETERR();
  EMITERRQ(STACK, __func__);

  if (*msg) {
    free(*msg);
    *msg = NULL;
  }
  return ierr;
CLEAN_UP:
  return FATAL;
}
