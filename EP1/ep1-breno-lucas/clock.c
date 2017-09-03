#include "clock.h"

double get_time(struct timeval start) {
    struct timeval cur;
    gettimeofday(&cur, NULL);
    double EQ = 1000000;
    double ret = (cur.tv_sec - start.tv_sec) + (cur.tv_usec - start.tv_usec) / EQ;
    return ret;
}
