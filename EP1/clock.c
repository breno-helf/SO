#include "clock.h"

double get_time(clock_t start, clock_t cur) {
    return (double)(cur - start) / CLOCKS_PER_SEC;
}
