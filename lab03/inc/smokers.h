#ifndef SMOKERS_H
#define SMOKERS_H

#include <semaphore.h>
extern sem_t tobacco_sem, paper_sem, match_sem, agent_sem;

typedef enum {
    SMOKER_TOBACCO,
    SMOKER_PAPER,
    SMOKER_MATCH
} smoker_arg;

void *smoker_thread_func(void *arg);

void smokers_init();

#endif