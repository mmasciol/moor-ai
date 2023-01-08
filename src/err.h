#ifndef MOOR_AI_ERROR_H
#define MOOR_AI_ERROR_H

typedef enum ERROR_CODE {
  SAFE,
  VERBOSE,
  INFO,
  WARNING,
  ERROR,
  FATAL,
} ERROR_CODE;

ERROR_CODE ierr_msg_set(char **msg, ERROR_CODE ierr, const ERROR_CODE new_ierr,
                       const char *file, int line, const char *in_string, ...);

void copy_string(char *tar, unsigned char *src);

#endif /* MOOR_AI_ERROR_H */
