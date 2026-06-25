#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "smokers.h"

static char *smoker_type_to_str[] = {
    [SMOKER_TOBACCO] = "Tabaco",
    [SMOKER_PAPER] = "Papel",
    [SMOKER_MATCH] = "Fósforo"
};

pthread_t s1, s2, s3;

void smoke(smoker_arg smoker_type){
    printf("O fumante com %s fumou!\n", smoker_type_to_str[smoker_type]);
    sleep(1);
}

void *smoker_thread_func(void *arg){
    while(1){
        smoker_arg current_arg = (smoker_arg) arg;

        switch(current_arg){
            case SMOKER_TOBACCO:
                sem_wait(&tobacco_sem);
                smoke(SMOKER_TOBACCO);
                break;

            case SMOKER_PAPER:
                sem_wait(&paper_sem);
                smoke(SMOKER_PAPER);
                break;

            case SMOKER_MATCH:
                sem_wait(&match_sem);
                smoke(SMOKER_MATCH);
                break;
        }

        sem_post(&agent_sem);

    }
    return NULL;
}
