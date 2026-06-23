#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// Semaphores
sem_t agent_semaphore;
sem_t smoker_semaphores[3];  // One for each smoker

// Thread function for the agent
void* agent_function(void* arg) {
    // Agent logic will go here
    return NULL;
}

// Thread function for smokers
void* smoker_function(void* arg) {
    int smoker_id = *(int*)arg;
    // Smoker logic will go here
    return NULL;
}

int main() {
    // Initialize semaphores
    sem_init(&agent_semaphore, 0, 1);  // Agent starts with 1 permit
    for (int i = 0; i < 3; i++) {
        sem_init(&smoker_semaphores[i], 0, 0);  // Smokers start blocked
    }

    // Create threads
    pthread_t agent_thread;
    pthread_t smoker_threads[3];
    int smoker_ids[3] = {0, 1, 2};

    // Create agent thread
    pthread_create(&agent_thread, NULL, agent_function, NULL);

    // Create smoker threads
    for (int i = 0; i < 3; i++) {
        pthread_create(&smoker_threads[i], NULL, smoker_function, &smoker_ids[i]);
    }

    // Wait for all threads to complete
    pthread_join(agent_thread, NULL);
    for (int i = 0; i < 3; i++) {
        pthread_join(smoker_threads[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&agent_semaphore);
    for (int i = 0; i < 3; i++) {
        sem_destroy(&smoker_semaphores[i]);
    }

    return 0;
}


