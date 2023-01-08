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
  // int n = 0;
  // char *scalar = NULL;
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
      message = bformat("Parser error [%d]", parser.error);
      EMITERRQ(FATAL, (const char *)message->data);
    }

    switch (event.type) {
    case YAML_NO_EVENT:
      puts("No event!");
      break;

    /* Stream start/end */
    case YAML_STREAM_START_EVENT:
      puts("STREAM START");
      break;
    case YAML_STREAM_END_EVENT:
      puts("STREAM END");
      break;

    /* Block delimeters */
    case YAML_DOCUMENT_START_EVENT:
      puts("<b>Start Document</b>");
      break;
    case YAML_DOCUMENT_END_EVENT:
      puts("<b>End Document</b>");
      break;
    case YAML_SEQUENCE_START_EVENT:
      puts("<b>Start Sequence</b>");
      break;
    case YAML_SEQUENCE_END_EVENT:
      puts("<b>End Sequence</b>");
      break;
    case YAML_MAPPING_START_EVENT:
      ierr = parse_mapping(d, &parser, &event, msg);
      puts("  <b>Start Mapping</b>");
      break;
    case YAML_MAPPING_END_EVENT:
      puts("  <b>End Mapping</b>");
      break;

    /* Data */
    case YAML_ALIAS_EVENT:
      // printf("Got alias (anchor %s)\n", event.data.alias.anchor);
      break;
    case YAML_SCALAR_EVENT:
      // DEALLOCATE(scalar);
      // n = strlen(event.data.scalar.value);
      // scalar = (char *)malloc((n + 1) * sizeof(char));
      // copy_string(scalar, event.data.scalar.value);
      printf("    Got scalar (value %s)\n", event.data.scalar.value);
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

ERROR_CODE parse_mapping(Domain *d, yaml_parser_t *p, yaml_event_t *e,
                        char **msg)
{
  ERROR_CODE ierr = SAFE;
  bstring message = NULL;
  char *s = NULL;
  int n = 0;
  EMITERRQ(STACK, __func__);

  if (!yaml_parser_parse(p, e)) {
    message = bformat("Parser error [%d]", p->error);
    EMITERRQ(FATAL, (const char *)message->data);
  }

  if (e->type != YAML_SCALAR_EVENT) {
    message = bformat("Parser error [%d]. Failed to retrieve mapping field.",
                     p->error);
    EMITERRQ(FATAL, (const char *)message->data);
  }

  n = strlen(e->data.scalar.value);
  s = (char *)malloc((n + 1) * sizeof(char));
  copy_string(s, e->data.scalar.value);

  yaml_event_delete(e);

  printf("\n\n{ %s\n", s);
  // do {
  //   if (!yaml_parser_parse(p, e)) {
  //     message = bformat("Parser error %d\n", p->error);
  //     EMITERRQ(FATAL, (const char *)message->data);
  //   }
  //
  //   switch (e->type) {
  //   case YAML_MAPPING_END_EVENT:
  //     printf("}\n\n");
  //     DEALLOCATE(s);
  //     return ierr;
  //   case YAML_SCALAR_EVENT:
  //     //if (strcmp(e->data.scalar.value, "info") == 0) {
  //     //  printf("    --> scalar (value %s [%ld])\n", e->data.scalar.value, strlen(e->data.scalar.value));
  //     //} //else if (strcmp(e->data.scalar.value, "line_properties") == 0) {
  //     printf("    --> scalar (value %s [%ld])\n", e->data.scalar.value, strlen(e->data.scalar.value));
  //     //}
  //     break;
  //   }
  //
  //   if (e->type != YAML_STREAM_END_EVENT) {
  //     yaml_event_delete(e);
  //   }
  // } while (e->type != YAML_STREAM_END_EVENT);

  DEALLOCATE(s);
  return ierr;
CLEAN_UP:
  DEALLOCATE(s);
  bdestroy(message);
  return FATAL;
}
