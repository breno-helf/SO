#ifndef EVENT
#define EVENT

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

static int show_event;

void event(const char * msg, ...);
void update_show(int up);

#endif
