#ifndef CTERATOR_H
#define CTERATOR_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>


// --------------- CLCP ---------------
typedef enum {
    LEVEL_FATAL = 0,
    LEVEL_WARN  = 1,
    LEVEL_DEBUG = 2,
    LEVEL_TODO  = 3,
    LEVEL_UNIMPLEMENTED = 4
} LogLevel;

static const char* const LEVEL_NAMES[] = {
    "FATAL", "WARN", "DEBUG", "TODO", "UNIMPLEMENTED"
};

static inline void lmessage(LogLevel level, const char* format, ...) {
    fprintf(stderr, "[%s] ", LEVEL_NAMES[level]);

    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);

    fprintf(stderr, "\n");

    if (level == LEVEL_FATAL || level == LEVEL_UNIMPLEMENTED) {
        exit(1);
    }
}

#define lfatal(...) lmessage(LEVEL_FATAL, __VA_ARGS__)
#define lwarn(...)  lmessage(LEVEL_WARN, __VA_ARGS__)
#define ldebug(...) lmessage(LEVEL_DEBUG, __VA_ARGS__)
#define ltodo(...)  lmessage(LEVEL_TODO, __VA_ARGS__)
#define lunimp(...) lmessage(LEVEL_UNIMPLEMENTED, "Not implemented: " __VA_ARGS__)
//------------------------------

typedef struct cterator {
    void **items;
    size_t count;
    size_t current;
} cterator;

#define foreach(item, iterator) \
    for(int _keep = (ct_next(iterator) ? 1 : 0); \
        _keep && ((item = ct_get(iterator)) || 1); \
        _keep = ct_next(iterator) ? 1 : 0)

cterator *new_cterator(void **items , size_t count);
void free_cterator(cterator *ct);

void *ct_get(cterator *ct);
int ct_next(cterator *ct);
void ct_reset(cterator *ct);

#endif
