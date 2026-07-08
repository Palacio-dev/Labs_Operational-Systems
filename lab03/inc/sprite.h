#ifndef SPRITE_H
#define SPRITE_H

typedef struct {
    int x;
    int y;
    char *og_text;
    int *colors;
    char text[4];
    int y0;
} sprite;

#endif