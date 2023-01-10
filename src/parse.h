#ifndef MOOR_AI_PARSE_YAML_H
#define MOOR_AI_PARSE_YAML_H

#include "def.h"
#include "err.h"
#include "yaml.h"

typedef struct ParserContainerT {
  char *key;
  char **bag;
  size_t nbag;
  yaml_parser_t *parser;
  yaml_event_t *event;
} ParserContainer;

ERROR_CODE parse_yaml(Domain *d, char *fpath, char **msg);
// ERROR_CODE parse_mapping(Domain *d, yaml_parser_t *p, yaml_event_t *e,
//                         char **msg);
ERROR_CODE parse_recurse_yaml(Domain *d, ParserContainer *c, char **msg);
ERROR_CODE parser_add_to_bag(ParserContainer *c, const char *word, char **msg);

#endif /* MOOR_AI_PARSE_YAML_H */
