#ifndef LOGGING_H
#define LOGGING_H

#include "common.h"

/* ========================================================================== */
/* LOGGIN MACROSS                                                             */
/* ========================================================================== */

#define LOG_ERROR(format, ...) \
    pd->system->error("ERROR: %s: " format, __func__, ##__VA_ARGS__)

#define LOG_WARNING(format, ...) \
    pd->system->logToConsole("WARNING: %s: " format, __func__, ##__VA_ARGS__)

#endif /* LOGGING_H */
