#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include "../inc/agent.h"

pthread_t thread_A, thread_B, thread_C;
sem_t agent_sem, tobacco, paper, match;

void *agent_thread_func(void *arg){
    int counter = 0;
    while(1){
        agent_arg current_arg = (agent_arg) arg;

        sem_wait(&agent_sem);

        printf("Thread do agente ativada (%d)! Iteração = %d\n", current_arg, counter);

        sleep(1);

        if (current_arg == TOBACCO_AND_PAPER){
            sem_post(&tobacco);
            sem_post(&paper);
        } else if (current_arg == TOBACCO_AND_MATCH){
            sem_post(&tobacco);
            sem_post(&match);
        } else if (current_arg == MATCH_AND_PAPER){
            sem_post(&match);
            sem_post(&paper);
        }

        counter++;
    }
    return NULL;
}