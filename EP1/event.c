#include "event.h"

void event(const char *msg, ...) { 
    char * error_msg;

    if (show_event) {
	if (msg) {
	    va_list arglist;
	    int tam = strlen(msg) + 1000;
	    error_msg = malloc(sizeof(char) * tam);
				      
	    va_start(arglist, msg);
	    vsnprintf(error_msg, tam, msg, arglist);
	    va_end(arglist);
	}

	fprintf(stderr, "%s", error_msg);
	free(error_msg);
    }
}

void update_show(int up) {
    show_event = up;
}
