#ifndef EVENT
#define EVENT

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

/*
  Print event message in stderr if the static
  variable is one. Static variable inicializes
  with 0 and change value if message is NULL
*/
void event(const char * msg, ...);

#endif
