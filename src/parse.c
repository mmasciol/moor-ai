#include <stdio.h>

#include "bstrlib.h"
#include "def.h"
#include "parse.h"
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

  tree.block = NONE;
  tree.label = NULL;
  tree.f = NULL;
  tree.child = NULL;
  tree.nchild = 0;

  yaml_parser_set_input_file(&p.parser, fh);
  ierr = parse_recurse_yaml(&tree, &p, msg);
  ierr = parse_free_yaml_tree(&tree, msg);
  yaml_event_delete(&p.event);

  yaml_parser_delete(&p.parser);
  fclose(fh);

  return ierr;
CLEAN_UP:
  yaml_parser_delete(&p.parser);
  bdestroy(message);
  return FATAL;
}

ERROR_CODE parse_recurse_yaml(YamlTree *this, ParserEvents *p, char **msg)
{
  ERROR_CODE ierr = SAFE;
  bstring message = NULL;
  char current_field[256];

  EMITERRQ(STACK, __func__);

  current_field[0] = '\0';
  // if (!current_field[0]) checkpoint();

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
    case YAML_SEQUENCE_START_EVENT:
      puts("  <<Sequence Start>>");
      ierr = parse_append_yaml_branch(this, msg);
      this->child[this->nchild - 1].block = SEQUENCE;
      ierr = parse_recurse_yaml(&this->child[this->nchild - 1], p, msg);
      break;
    case YAML_SEQUENCE_END_EVENT:
      puts("  <<Sequence End>>");
      return ierr;
      break;
    case YAML_MAPPING_START_EVENT:
      puts("  <<Mapping Start>>");
      ierr = parse_append_yaml_branch(this, msg);
      // printf("   >>> %ld\n", this->nchild);
      this->child[this->nchild - 1].block = MAP;
      ierr = parse_recurse_yaml(&this->child[this->nchild - 1], p, msg);
      break;
    case YAML_MAPPING_END_EVENT:
      puts("  <<Mapping End>>");
      return ierr;
      break;


    /* Data */
    case YAML_ALIAS_EVENT:
      break;
    case YAML_SCALAR_EVENT:
      // printf("    Got scalar (value %s)\n", p->event.data.scalar.value);
      if (this->block == MAP) {
        if (current_field[0] != '\0') {
          // printf("bloc: [%d]\n", this->block);
          printf("-----> %s:  %s\n", current_field, p->event.data.scalar.value);
          current_field[0] = '\0';
        } else {
          copy_string(current_field, p->event.data.scalar.value);
        }
      }
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

// ERROR_CODE parse_add_to_bag(YamlTree *t, const char *word, char **msg)
// {
//   ERROR_CODE ierr = SAFE;
//   EMITERRQ(STACK, __func__);
//
//   // if (!t->field) {
//   //   t->field = malloc(sizeof(char *));
//   // } else {
//   //   t->field = realloc(t->field, (t->nfield + 1) * sizeof(char *));
//   // }
//   // t->nfield += 1;
//   // t->field[t->nfield - 1] = malloc((strlen(word) + 1) * sizeof(char));
//   // copy_string(t->field[t->nfield - 1], (unsigned char *)word);
//
//   return ierr;
// CLEAN_UP:
//   return FATAL;
// }

ERROR_CODE parse_append_yaml_branch(YamlTree *t, char **msg)
{
  ERROR_CODE ierr = SAFE;

  EMITERRQ(STACK, __func__);

  if (!t->child) {
    t->child = malloc(1 * sizeof(YamlTree));
  } else {
    t->child = realloc(t->child, (t->nchild + 1) * sizeof(YamlTree));
  }

  t->nchild++;

  t->child[t->nchild - 1].block = NONE;
  t->child[t->nchild - 1].label = NULL;
  t->child[t->nchild - 1].f = NULL;
  t->child[t->nchild - 1].child = NULL;
  t->child[t->nchild - 1].nchild = 0;

  return ierr;
CLEAN_UP:
  return FATAL;
}

ERROR_CODE parse_free_yaml_tree(YamlTree *c, char **msg)
{
  ERROR_CODE ierr = SAFE;

  EMITERRQ(STACK, __func__);

  if (c->child) {
    ierr = parse_free_yaml_tree(c->child, msg);
    free(c->child);
  }

  return ierr;
CLEAN_UP:
  return FATAL;
}
