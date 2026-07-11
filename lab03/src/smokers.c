#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "smokers.h"
#include "sprite.h"
#include "anim.h"

/*static char *smoker_type_to_str[] = {
    [SMOKER_TOBACCO] = "Tabaco",
    [SMOKER_PAPER] = "Papel",
    [SMOKER_MATCH] = "Fósforo"
};*/

sprite smoker_tobacco = {
    .x = 7,
    .y = 5,
    .og_text = "Ft",
    .colors = (int []){4, 2}
};
sprite smoker_paper = {
    .x = 7,
    .y = 6,
    .og_text = "Fp",
    .colors = (int []){4, 3}
};
sprite smoker_match = {
    .x = 7,
    .y = 7,
    .og_text = "Fm",
    .colors = (int []){4, 1}
};

pthread_t s1, s2, s3;

void smokers_init() {
    reset_text(&smoker_tobacco);
    reset_text(&smoker_paper);
    reset_text(&smoker_match);
    anim_show_sprite(&smoker_tobacco);
    anim_show_sprite(&smoker_paper);
    anim_show_sprite(&smoker_match);
}

void smoke(sprite *smoker_sprite, int time_smoking) {
    anim_print("Fumante %s notificado! Ele fumará por %d segundos", smoker_sprite->og_text, time_smoking);
    anim_smoking(smoker_sprite, time_smoking);
    sleep(1);
    anim_recharge(smoker_sprite);
}

void *smoker_thread_func(void *arg){
    while(1){
        smoker_arg current_arg = (smoker_arg) arg;

        switch(current_arg){
            case SMOKER_TOBACCO:
                sem_wait(&tobacco_sem);
                smoke(&smoker_tobacco, 4);
                break;

            case SMOKER_PAPER:
                sem_wait(&paper_sem);
                smoke(&smoker_paper, 2);
                break;

            case SMOKER_MATCH:
                sem_wait(&match_sem);
                smoke(&smoker_match, 5);
                break;
        }

        sem_post(&agent_sem);

    }
    return NULL;
}
