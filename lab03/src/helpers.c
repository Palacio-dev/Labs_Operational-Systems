#include <pthread.h>
#include <stdbool.h>
#include "helpers.h"

pthread_t h1, h2, h3;
pthread_mutex_t helpers_mutex;
sem_t tobacco_sem, paper_sem, match_sem;

static bool has_tobacco = false, has_paper = false, has_match = false;

void *helper_thread_func(void *arg){
    while(1){
        helper_arg current_arg = (helper_arg) arg;

        switch(current_arg){
            case TOBACCO:
                sem_wait(&tobacco);
                break;
            case PAPER:
                sem_wait(&paper);
                break;
            case MATCH:
                sem_wait(&match);
                break;
        }

        pthread_mutex_lock(&helpers_mutex);

        switch(current_arg){
            case TOBACCO:
                if (has_paper){
                    has_paper = false;
                    sem_post(&match_sem);
                } else if (has_match){
                    has_match = false;
                    sem_post(&paper_sem);
                } else {
                    has_tobacco = true;
                } break;

            case PAPER:
                if (has_tobacco){
                    has_tobacco = false;
                    sem_post(&match_sem);
                } else if (has_match){
                    has_match = false;
                    sem_post(&tobacco_sem);
                } else {
                    has_paper = true;
                } break;

            case MATCH:
                if (has_tobacco){
                    has_tobacco = false;
                    sem_post(&paper_sem);
                } else if (has_paper){
                    has_paper = false;
                    sem_post(&tobacco_sem);
                } else {
                    has_match = true;
                } break;
        }

        pthread_mutex_unlock(&helpers_mutex);

    }
    return NULL;
}