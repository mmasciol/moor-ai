#ifndef MOOR_AI_PARSE_YAML_H
#define MOOR_AI_PARSE_YAML_H

#include "def.h"
#include "err.h"
#include "yaml.h"

ERROR_CODE parse_yaml(Domain *d, char *fpath, char **msg);
ERROR_CODE parse_mapping(Domain *d, yaml_parser_t *p, yaml_event_t *e,
                        char **msg);

#endif /* MOOR_AI_PARSE_YAML_H */
