#include "initializeClock.h"
#include <time.h>
#include <sys/time.h>

// Diese Werte sollten während des Build-Prozesses ersetzt werden
#define COMPILE_DATE __DATE__
#define COMPILE_TIME __TIME__

void initializeClock() {
    struct tm tm;
    strptime(COMPILE_DATE " " COMPILE_TIME, "%b %d %Y %H:%M:%S", &tm);
    time_t t = mktime(&tm);

    struct timeval now = { .tv_sec = t, .tv_usec = 0 };
    settimeofday(&now, NULL);
}
