#ifndef SPRITE_H
#define SPRITE_H

struct Sprite {
    int x;
    int y;
    char image;
    int color;
};

void *agent_thread_func(void *arg);

#endif