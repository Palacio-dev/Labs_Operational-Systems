#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include "agent.h"
#include "sprite.h"
#include "anim.h"

pthread_t thread_A, thread_B, thread_C;
sem_t agent_sem, tobacco, paper, match;

sprite agent_mt = {
    .x = 42,
    .y = 5,
    .og_text = "Amt",
    .colors = (int []){5, 1, 2}
};
sprite agent_pt = {
    .x = 42,
    .y = 6,
    .og_text = "Apt",
    .colors = (int []){5, 3, 2}
};
sprite agent_mp = {
    .x = 42,
    .y = 7,
    .og_text = "Amp",
    .colors = (int []){5, 1, 3}
};

void agents_init(){
    reset_text(&agent_mt);
    reset_text(&agent_pt);
    reset_text(&agent_mp);
    anim_show_sprite(&agent_mt);
    anim_show_sprite(&agent_pt);
    anim_show_sprite(&agent_mp);
}

void *agent_thread_func(void *arg){
    // int counter = 0;
    while(1){
        agent_arg current_arg = (agent_arg) arg;

        sem_wait(&agent_sem);

        printf("Thread do agente ativada (%d)! Iteração = %d\n", current_arg, counter);

        sleep(1);

        if (current_arg == TOBACCO_AND_PAPER){
            anim_agent_1(&agent_pt);
            
            sem_post(&tobacco);
            sem_post(&paper);

            anim_agent_2(&agent_pt);

            // tempo de recarregamento dos materiais
            sleep(2);
            anim_recharge(&agent_pt);

        } else if (current_arg == TOBACCO_AND_MATCH){
            anim_agent_1(&agent_mt);
            
            sem_post(&tobacco);
            sem_post(&match);

            anim_agent_2(&agent_mt);
            
            // tempo de recarregamento dos materiais
            sleep(3);
            anim_recharge(&agent_mt);

        } else if (current_arg == MATCH_AND_PAPER){
            anim_agent_1(&agent_mp);
            
            sem_post(&match);
            sem_post(&paper);

            anim_agent_2(&agent_mp);

            // tempo de recarregamento dos materiais
            sleep(1);
            anim_recharge(&agent_mp);
        }

        // counter++;
    }
    return NULL;
}