#ifndef ANIM_H
#define ANIM_H

#include "sprite.h"
#include <pthread.h>

extern pthread_mutex_t screen_mutex;


void anim_init();

void anim_close();

void reset_text(sprite *s);

void move_sprite(sprite *s, int x_plus, int y_plus);

void draw_sprite(sprite *s);

void anim_recharge(sprite *s);

void anim_show_sprite(sprite *s);

void anim_smoking(sprite *s, int time_smoking);

void anim_agent_1(sprite *s);

void anim_agent_2(sprite *s);

void anim_draw_cenario();

#endif