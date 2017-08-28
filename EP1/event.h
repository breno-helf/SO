#ifndef EVENT
#define EVENT

#include <stdio.h>
#include <stdlib.h>

static int show_event = 0;

#define event(...) { if (show_event) { fprintf(stderr, __VA_ARGS__); } }

#endif
