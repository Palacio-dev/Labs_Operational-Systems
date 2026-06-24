#ifndef HELPERS_H
#define HELPERS_H

#include <semaphore.h>
extern sem_t tobacco, paper, match;

typedef enum {
    TOBACCO,
    PAPER,
    MATCH
} helper_arg;

void *helper_thread_func(void *arg);

#endif