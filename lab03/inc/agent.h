#ifndef AGENT_H
#define AGENT_H

typedef enum {
    TOBACCO_AND_PAPER,
    TOBACCO_AND_MATCH,
    MATCH_AND_PAPER
} agent_arg;

void *agent_thread_func(void *arg);

#endif