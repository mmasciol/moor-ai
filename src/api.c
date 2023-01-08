// https://stackoverflow.com/questions/1398307/how-can-i-allocate-memory-and-return-it-via-a-pointer-parameter-to-the-calling

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "api.h"
#include "bstrlib.h"
#include "def.h"
#include "sys.h"
#include "yaml.h"

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
  yaml_parser_t parser;
  yaml_token_t  token;
  FILE *file = NULL;

  RESETERR();
  CHECKERRQ(VERBOSE, __func__);

  message = bformat("Reading *.yaml file <%s>", fpath);
  CHECKERRQ(INFO, (const char*)message->data);
  bdestroy(message);

  file = fopen(fpath, "rb");
  yaml_parser_initialize(&parser);
  yaml_parser_set_input_file(&parser, file);

do {
    yaml_parser_scan(&parser, &token);
    switch(token.type)
    {
    /* Stream start/end */
    case YAML_STREAM_START_TOKEN: puts("STREAM START"); break;
    case YAML_STREAM_END_TOKEN:   puts("STREAM END");   break;
    /* Token types (read before actual token) */
    case YAML_KEY_TOKEN:   printf("(Key token)   "); break;
    case YAML_VALUE_TOKEN: printf("(Value token) "); break;
    /* Block delimeters */
    case YAML_BLOCK_SEQUENCE_START_TOKEN: puts("<b>Start Block (Sequence)</b>"); break;
    case YAML_BLOCK_ENTRY_TOKEN:          puts("<b>Start Block (Entry)</b>");    break;
    case YAML_BLOCK_END_TOKEN:            puts("<b>End block</b>");              break;
    /* Data */
    case YAML_BLOCK_MAPPING_START_TOKEN:  puts("[Block mapping]");            break;
    case YAML_SCALAR_TOKEN:  printf("scalar %s \n", token.data.scalar.value); break;
    /* Others */
    default:
      printf("Got token of type %d\n", token.type);
    }
    if(token.type != YAML_STREAM_END_TOKEN)
      yaml_token_delete(&token);
  } while(token.type != YAML_STREAM_END_TOKEN);
  yaml_token_delete(&token);

  yaml_parser_delete(&parser);
  fclose(file);

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
