#include <stdio.h>
#include <stdlib.h>

int show_event = 0;

#define event(args...) { if (show_event) { fprintf(stderr, args); } }

