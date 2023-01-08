#include <stdio.h>

#include "bstrlib.h"
#include "def.h"
#include "parse.h"
#include "sys.h"
#include "yaml.h"

ERROR_CODE parse_yaml(Domain *d, char *fpath, char **msg)
{
  ERROR_CODE ierr = SAFE;
  bstring message = NULL;
  FILE *fh = NULL;
  yaml_parser_t parser;
  yaml_event_t event;

  EMITERRQ(STACK, __func__);

  fh = fopen(fpath, "r");

  if (!yaml_parser_initialize(&parser)) {
    message = bformat("Failed to initialize parser *.yaml file <%s>", fpath);
    EMITERRQ(FATAL, (const char *)message->data);
  }

  if (fh == NULL) {
    message = bformat("Failed to open *.yaml file <%s>", fpath);
    EMITERRQ(FATAL, (const char *)message->data);
  }

  yaml_parser_set_input_file(&parser, fh);

  do {
    if (!yaml_parser_parse(&parser, &event)) {
      printf("Parser error %d\n", parser.error);
      exit(EXIT_FAILURE);
    }

    switch (event.type) {
    case YAML_NO_EVENT:
      // puts("No event!");
      break;

    /* Stream start/end */
    case YAML_STREAM_START_EVENT:
      // puts("STREAM START");
      break;
    case YAML_STREAM_END_EVENT:
      // puts("STREAM END");
      break;

    /* Block delimeters */
    case YAML_DOCUMENT_START_EVENT:
      // puts("<b>Start Document</b>");
      break;
    case YAML_DOCUMENT_END_EVENT:
      // puts("<b>End Document</b>");
      break;
    case YAML_SEQUENCE_START_EVENT:
      // puts("<b>Start Sequence</b>");
      break;
    case YAML_SEQUENCE_END_EVENT:
      // puts("<b>End Sequence</b>");
      break;
    case YAML_MAPPING_START_EVENT:
      // puts("<b>Start Mapping</b>");
      break;
    case YAML_MAPPING_END_EVENT:
      puts("<b>End Mapping</b>");
      break;

    /* Data */
    case YAML_ALIAS_EVENT:
      // printf("Got alias (anchor %s)\n", event.data.alias.anchor);
      break;
    case YAML_SCALAR_EVENT:
      printf("Got scalar (value %s)\n", event.data.scalar.value);
      break;
    }

    if (event.type != YAML_STREAM_END_EVENT) {
      yaml_event_delete(&event);
    }
  } while (event.type != YAML_STREAM_END_EVENT);
  yaml_event_delete(&event);

  yaml_parser_delete(&parser);
  fclose(fh);

  return ierr;
CLEAN_UP:
  yaml_parser_delete(&parser);
  bdestroy(message);
  return FATAL;
}
