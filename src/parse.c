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
  // char *s = NULL;
  yaml_parser_t parser;
  yaml_event_t event;
  ParserContainer container;

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

  container.parser = &parser;
  container.event = &event;
  container.key = NULL;
  container.bag = NULL;
  container.nbag = 0;
  yaml_parser_set_input_file(&parser, fh);
  ierr = parse_recurse_yaml(d, &container, msg);
  // do {
  //   if (!yaml_parser_parse(&parser, &event)) {
  //     message = bformat("Parser error [%d]", parser.error);
  //     EMITERRQ(FATAL, (const char *)message->data);
  //   }
  //
  //   switch (event.type) {
  //   case YAML_NO_EVENT:
  //     puts("No event!");
  //     break;
  //
  //   /* Stream start/end */
  //   case YAML_STREAM_START_EVENT:
  //     puts("STREAM START");
  //     break;
  //   case YAML_STREAM_END_EVENT:
  //     puts("STREAM END");
  //     break;
  //
  //   /* Block delimeters */
  //   case YAML_DOCUMENT_START_EVENT:
  //     puts("<b>Start Document</b>");
  //     break;
  //   case YAML_DOCUMENT_END_EVENT:
  //     puts("<b>End Document</b>");
  //     break;
  //   case YAML_SEQUENCE_START_EVENT:
  //     puts("<b>Start Sequence</b>");
  //     break;
  //   case YAML_SEQUENCE_END_EVENT:
  //     puts("<b>End Sequence</b>");
  //     break;
  //   case YAML_MAPPING_START_EVENT:
  //     // ierr = parse_mapping(d, &parser, &event, msg);
  //     puts("  <b>Start Mapping</b>");
  //     break;
  //   case YAML_MAPPING_END_EVENT:
  //     puts("  <b>End Mapping</b>");
  //     break;
  //
  //   /* Data */
  //   case YAML_ALIAS_EVENT:
  //     // printf("Got alias (anchor %s)\n", event.data.alias.anchor);
  //     break;
  //   case YAML_SCALAR_EVENT:
  //     // DEALLOCATE(scalar);
  //     // n = strlen(event.data.scalar.value);
  //     // scalar = (char *)malloc((n + 1) * sizeof(char));
  //     // copy_string(scalar, event.data.scalar.value);
  //     printf("    Got scalar (value %s)\n", event.data.scalar.value);
  //     break;
  //   }
  //
  //   if (event.type != YAML_STREAM_END_EVENT) {
  //     yaml_event_delete(&event);
  //   }
  // } while (event.type != YAML_STREAM_END_EVENT);
  yaml_event_delete(&event);

  yaml_parser_delete(&parser);
  fclose(fh);
  // DEALLOCATE(s);

  return ierr;
CLEAN_UP:
  // DEALLOCATE(s);
  yaml_parser_delete(&parser);
  bdestroy(message);
  return FATAL;
}

ERROR_CODE parse_recurse_yaml(Domain *d, ParserContainer *parent, char **msg)
{
  ERROR_CODE ierr = SAFE;
  bstring message = NULL;
  int n = 0;
  char s[1024];
  ParserContainer container;
  EMITERRQ(STACK, __func__);

  container.parser = parent->parser;
  container.event = parent->event;
  container.key = NULL;
  container.bag = NULL;
  container.nbag = 0;

  do {
    if (!yaml_parser_parse(parent->parser, parent->event)) {
      message = bformat("Parser error [%d]", parent->parser->error);
      EMITERRQ(FATAL, (const char *)message->data);
    }

    switch (parent->event->type) {
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
      puts("  <<Sequence Start>>");
      if (container.bag) {
        container.key = container.bag[container.nbag - 1];
      } else {
        container.key = parent->key;
      }
      ierr = parse_recurse_yaml(d, &container, msg);
      CHECKERRQ(FATAL, "Error parsing *.yaml");
      break;
    case YAML_SEQUENCE_END_EVENT:
      if (1 < container.nbag) {
        if (parent->key) {
         printf("  %s:\n", parent->key);
        }
      }
      // printf("    %s:  ", container.bag[0]);
      // for (int i = 1 ; i < container.nbag ; i++) {
      //   printf("%s,  \n", container.bag[i]);
      // }
      // printf("\n");
      yaml_event_delete(parent->event);
      DEALLOCATE2D(container.bag, container.nbag);
      puts("  <<Sequence End>>");
      return ierr;
      break;
    case YAML_MAPPING_START_EVENT:
      puts("  <<Mapping Start>>");
      if (container.bag) {
        container.key = container.bag[container.nbag - 1];
      } else {
        container.key = parent->key;
      }
      ierr = parse_recurse_yaml(d, &container, msg);
      CHECKERRQ(FATAL, "Error parsing *.yaml");
      break;
    case YAML_MAPPING_END_EVENT:
      if (parent->key) {
        printf("  %s:\n", parent->key);
      }
      for (int i = 0; i < container.nbag; i+=2) {
        printf("    %s:  %s\n", container.bag[i], container.bag[i + 1]);
      }
      yaml_event_delete(parent->event);
      DEALLOCATE2D(container.bag, container.nbag);
      puts("  <<Mapping End>>");
      return ierr;
      break;

    /* Data */
    case YAML_ALIAS_EVENT:
      break;
    case YAML_SCALAR_EVENT:
      n = strlen(parent->event->data.scalar.value);
      ierr =
         parser_add_to_bag(&container, parent->event->data.scalar.value, msg);
      // printf("    Got scalar (value %s)\n", parent->event->data.scalar.value);
      break;
    }

    if (parent->event->type != YAML_STREAM_END_EVENT) {
      yaml_event_delete(parent->event);
    }
  } while (parent->event->type != YAML_STREAM_END_EVENT);

  DEALLOCATE2D(container.bag, container.nbag);
  return ierr;
CLEAN_UP:
  DEALLOCATE2D(container.bag, container.nbag);
  bdestroy(message);
  return FATAL;
}

ERROR_CODE parser_add_to_bag(ParserContainer *c, const char *word, char **msg)
{
  ERROR_CODE ierr = SAFE;
  EMITERRQ(STACK, __func__);

  if (!c->bag) {
    c->bag = malloc(sizeof(char *));
  } else {
    c->bag = realloc(c->bag, (c->nbag + 1) * sizeof(char *));
  }
  c->nbag += 1;
  c->bag[c->nbag - 1] = malloc((strlen(word) + 1) * sizeof(char));
  copy_string(c->bag[c->nbag - 1], (unsigned char *)word);

  return ierr;
CLEAN_UP:
  return FATAL;
}
