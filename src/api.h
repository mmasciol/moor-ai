#ifndef MOOR_AI_API_H
#define MOOR_AI_API_H

#include "def.h"
#include "err.h"

ERROR_CODE api_allocate_domain(Domain **d, char **msg);
ERROR_CODE api_flush_msg(char **msg);
ERROR_CODE api_free_domain(Domain **d, char **msg);

#endif /* MOOR_AI_API_H */
