#include <stdio.h>

#include "bstrlib.h"
#include "err.h"
#include "sys.h"

ERROR_CODE ierr_msg_set(char **msg, ERROR_CODE ierr, const ERROR_CODE new_ierr,
                       const char *file, int line, const char *in_string, ...)
{
  va_list arglist;
  bstring prefix = NULL;
  bstring out_string = NULL;
  bstring user_msg = NULL;
  bstring message = NULL;
  const int START_VSNBUFF = 16;
  ERROR_CODE ret_ierr = SAFE;

  int r = 0;
  int n = 0;

  if (!msg) {
    message = bformat("");
  } else {
    message = bformat("%s", *msg);
  }

  /* This is a re-implementation of the bstring library routines 'bformat(...)
   * Take the variable argument list and create a string with it. This lets you
   * create a custom message to be printed to the terminal.
   */
  do {
    n = (int)(2 * strlen(in_string));
    if (n < START_VSNBUFF) {
      n = START_VSNBUFF;
    };
    user_msg = bfromcstralloc(n + 2, "");
    if (!user_msg) {
      n = 1;
      user_msg = bfromcstralloc(n + 2, "");
      if (!user_msg) {
       user_msg = NULL;
       break;
      };
    };
    while (1) {
      va_start(arglist, in_string);
      r = vsnprintf((char *)user_msg->data, n + 1, in_string, arglist);
      va_end(arglist);
      user_msg->data[n] = (unsigned char)'\0';
      user_msg->slen = (int)strlen((char *)user_msg->data);
      if (user_msg->slen < n) {
       break;
      };
      if (r > n) {
       n = r;
      } else {
       n += n;
      };
      if (0 != balloc(user_msg, n + 2)) {
       bdestroy(user_msg);
       break;
      };
    };
  } while (0);

  switch (new_ierr) {
  case SAFE:
    prefix = bformat("[SAFE   ]");
    break;
  case VERBOSE:
    prefix = bformat("[VERBOSE]");
    break;
  case INFO:
    prefix = bformat("[INFO   ]");
    break;
  case WARNING:
    prefix = bformat("[WARNING]");
    break;
  case ERROR:
    prefix = bformat("[ERROR  ]");
    break;
  case FATAL:
    prefix = bformat("[FATAL  ]");
    break;
  }

  if (new_ierr < ierr) {
    ret_ierr = ierr;
  } else {
    ret_ierr = new_ierr;
  }

  while (prefix->slen < 12) {
    bconchar(prefix, ' ');
  };

  out_string =
      bformat("%s(%s:%d) %s\n", prefix->data, file, line, user_msg->data);
  bconcat(message, out_string);

  copy_string(*msg, message->data);
  bdestroy(prefix);
  bdestroy(out_string);
  bdestroy(message);
  bdestroy(user_msg);

  return ret_ierr;
}

void copy_string(char *tar, unsigned char *src)
{
  while (*src) {
    *tar = *src;
    src++;
    tar++;
  };
  *tar = '\0';
}
