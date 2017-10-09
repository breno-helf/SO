#include "event.h"

void event(const char *msg, ...) { 
    char * error_msg;
    static int show_event = 0;

    if (msg == NULL) {
	show_event ^= 1;
	return;
    }

    if (show_event) {
	va_list arglist;
	int tam = strlen(msg) + 1000;
	error_msg = malloc(sizeof(char) * tam);
	
	va_start(arglist, msg);
	vsnprintf(error_msg, tam, msg, arglist);
	va_end(arglist);

	fprintf(stderr, "%s", error_msg);
	free(error_msg);
    }
}
