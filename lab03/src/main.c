#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include "agent.h"
#include "helpers.h"
#include "smokers.h"

extern pthread_t thread_A, thread_B, thread_C, h1, h2, h3, s1, s2, s3;
extern pthread_mutex_t helpers_mutex;

int main(){
    sem_t *semaphores[] = {&agent_sem, &tobacco, &paper, &match, &tobacco_sem, &paper_sem, &match_sem};
    for(long unsigned int i = 0; i < (sizeof(semaphores) / sizeof(semaphores[0])); i++){
        sem_init(semaphores[i], 0, 0);
    }

    pthread_mutex_init(&helpers_mutex, NULL);

    // criando threads do agente
    pthread_create(&thread_A, NULL, agent_thread_func, (void *) TOBACCO_AND_PAPER);
    pthread_create(&thread_B, NULL, agent_thread_func, (void *) TOBACCO_AND_MATCH);
    pthread_create(&thread_C, NULL, agent_thread_func, (void *) MATCH_AND_PAPER);

    // criando threads helpers
    pthread_create(&h1, NULL, helper_thread_func, (void *) TOBACCO);
    pthread_create(&h2, NULL, helper_thread_func, (void *) PAPER);
    pthread_create(&h3, NULL, helper_thread_func, (void *) MATCH);

    // criando threads dos smokers
    pthread_create(&s1, NULL, smoker_thread_func, (void *) SMOKER_TOBACCO);
    pthread_create(&s2, NULL, smoker_thread_func, (void *) SMOKER_PAPER);
    pthread_create(&s3, NULL, smoker_thread_func, (void *) SMOKER_MATCH);

    sem_post(&agent_sem);

    sleep(1000000);
}