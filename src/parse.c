#include <stdio.h>

#include "bstrlib.h"
#include "def.h"
#include "parse.h"
#include "simclist.h"
#include "sys.h"
#include "yaml.h"

ERROR_CODE parse_yaml(Domain *d, char *fpath, char **msg)
{
  // https://www.wpsoftware.net/andrew/pages/libyaml.html
  ERROR_CODE ierr = SAFE;
  bstring message = NULL;
  FILE *fh = NULL;
  ParserEvents p;
  YamlTree tree;

  EMITERRQ(STACK, __func__);

  fh = fopen(fpath, "r");

  if (!yaml_parser_initialize(&p.parser)) {
    message = bformat("Failed to initialize parser *.yaml file <%s>", fpath);
    EMITERRQ(FATAL, (const char *)message->data);
  }

  if (fh == NULL) {
    message = bformat("Failed to open *.yaml file <%s>", fpath);
    EMITERRQ(FATAL, (const char *)message->data);
  }

  tree.label = NULL;
  tree.f = NULL;
  list_init(&tree.fields);
  tree.nchild = 0;

  yaml_parser_set_input_file(&p.parser, fh);
  ierr = parse_recurse_yaml(&tree, &p, msg);
  ierr = parse_free_yaml_tree(&tree, msg);
  yaml_event_delete(&p.event);

  yaml_parser_delete(&p.parser);
  fclose(fh);
  list_destroy(&tree.fields);

  return ierr;
CLEAN_UP:
  yaml_parser_delete(&p.parser);
  bdestroy(message);
  return FATAL;
}

ERROR_CODE parse_recurse_yaml(YamlTree *t, ParserEvents *p, char **msg)
{
  ERROR_CODE ierr = SAFE;
  bstring message = NULL;
  char label[256];
  Field new_field;
  Field *field = NULL;

  EMITERRQ(STACK, __func__);

  label[0] = '\0';

  do {
    if (!yaml_parser_parse(&p->parser, &p->event)) {
      message = bformat("Parser error [%d]", p->parser.error);
      EMITERRQ(FATAL, (const char *)message->data);
    }

    switch (p->event.type) {
    case YAML_NO_EVENT:
      // puts("No event!");
      break;

    /* Stream start/end */
    case YAML_STREAM_START_EVENT:
      break;
    case YAML_STREAM_END_EVENT:
      break;


    /* Block delimeters */
    case YAML_DOCUMENT_START_EVENT:
      puts("<b>Start Document</b>");
      break;
    case YAML_DOCUMENT_END_EVENT:
      puts("<b>End Document</b>");
      break;

    case YAML_SEQUENCE_END_EVENT:
      puts("  <<Sequence End>>");
      return ierr;
      break;
    case YAML_MAPPING_END_EVENT:
      puts("  <<Mapping End>>");
      return ierr;
      break;

    case YAML_MAPPING_START_EVENT:
      puts("  <<Mapping Start>>");
      list_append(&t->fields, &new_field);
      field = (Field *)list_get_max(&t->fields);
      checkpoint();
      field->block = 0;
      checkpoint();
      ierr = parse_recurse_yaml(t, p, msg);
      field = NULL;
      break;
    case YAML_SEQUENCE_START_EVENT:
      puts("  <<Sequence Start>>");
      list_append(&t->fields, &new_field);
      field = (Field *)list_get_max(&t->fields);
      checkpoint();
      field->block = 0;
      checkpoint();
      ierr = parse_recurse_yaml(t, p, msg);
      field = NULL;
      break;


    /* Data */
    case YAML_ALIAS_EVENT:
      break;
    case YAML_SCALAR_EVENT:
      // printf("    Got scalar (value %s)\n", p->event.data.scalar.value);
      // if (this->block == MAP) {
      //   if (current_field[0] != '\0') {
      //     // printf("bloc: [%d]\n", this->block);
      //     current_field[0] = '\0';
      //   } else {
      // copy_string(label, p->event.data.scalar.value);
      // printf("-----> %s:  %s\n", label, p->event.data.scalar.value);
      //   }
      // }
      break;
    }

    if (p->event.type != YAML_STREAM_END_EVENT) {
      yaml_event_delete(&p->event);
    }
  } while (p->event.type != YAML_STREAM_END_EVENT);
  //
  //   DEALLOCATE2D(child.field, child.nfield);
  return ierr;
CLEAN_UP:
  //   DEALLOCATE2D(child.field, child.nfield);
  bdestroy(message);
  return FATAL;
}

ERROR_CODE parse_append_yaml_branch(YamlTree *t, char **msg)
{
  ERROR_CODE ierr = SAFE;

  EMITERRQ(STACK, __func__);

  // if (!t->child) {
  //   t->child = malloc(1 * sizeof(YamlTree));
  // } else {
  //   t->child = realloc(t->child, (t->nchild + 1) * sizeof(YamlTree));
  // }

  // t->nchild++;

  // t->child[t->nchild - 1].block = NONE;
  // t->child[t->nchild - 1].label = NULL;
  // t->child[t->nchild - 1].f = NULL;
  // t->child[t->nchild - 1].child = NULL;
  // t->child[t->nchild - 1].nchild = 0;

  return ierr;
CLEAN_UP:
  return FATAL;
}

ERROR_CODE parse_free_yaml_tree(YamlTree *c, char **msg)
{
  ERROR_CODE ierr = SAFE;

  EMITERRQ(STACK, __func__);

  // if (c->child) {
  //   ierr = parse_free_yaml_tree(c->child, msg);
  //   free(c->child);
  // }

  return ierr;
CLEAN_UP:
  return FATAL;
}

size_t _list_field_meter(const void *el)
{
  return sizeof(Field);
}
