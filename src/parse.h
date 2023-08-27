#ifndef MOOR_AI_PARSE_YAML_H
#define MOOR_AI_PARSE_YAML_H

#include "def.h"
#include "err.h"
#include "simclist.h"
#include "yaml.h"

typedef enum BLOCK_TYPE {
  NONE,
  MAP,
  SEQUENCE,
} BLOCK_TYPE;

typedef struct Field_t {
  char *field;
  char **key;
  char **value;
  size_t nkey;
  size_t nvalue;
  BLOCK_TYPE block;
} Field;

typedef struct YamlTree_t {
  char *label;
  Field *f;
  // struct YamlTree_t *child;
  list_t fields;
  size_t nchild;
  // BLOCK_TYPE block;
} YamlTree;

typedef struct ParserEvents_t {
  yaml_parser_t parser;
  yaml_event_t event;
} ParserEvents;

size_t _list_field_meter(const void *el);
ERROR_CODE parse_yaml(Domain *d, char *fpath, char **msg);
ERROR_CODE parse_recurse_yaml(YamlTree *t, ParserEvents *p, char **msg);
ERROR_CODE parse_append_yaml_branch(YamlTree *t, char **msg);
ERROR_CODE parse_free_yaml_tree(YamlTree *t, char **msg);

#endif /* MOOR_AI_PARSE_YAML_H */
