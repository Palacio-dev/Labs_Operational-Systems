#include <ncurses.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include "anim.h"

#define LOCK_SCREEN() pthread_mutex_lock(&screen_mutex);
#define UNLOCK_SCREEN() pthread_mutex_unlock(&screen_mutex);

#define ANIM_TIME_MULTIPLIER 1

#define PRINT_START 20
#define PRINT_END 27

static int print_line_count = PRINT_START;

pthread_mutex_t screen_mutex;

void msleep(unsigned int milliseconds) {
    // 1 millisecond = 1000 microseconds
    usleep(milliseconds * 1000 * ANIM_TIME_MULTIPLIER); 
}

void anim_init() {
    LOCK_SCREEN();

    initscr();
    noecho();
    curs_set(FALSE);
    start_color();

    use_default_colors();

    //init_pair(99, COLOR_WHITE, COLOR_BLACK); 
    //bkgd(COLOR_PAIR(99));
    
    init_pair(1, COLOR_RED, -1);       // Fósforo
    init_pair(2, COLOR_GREEN, -1);     // Tabaco
    init_pair(3, COLOR_BLUE, -1);      // Papel
    init_pair(4, COLOR_YELLOW, -1);    // Fumantes
    init_pair(5, COLOR_MAGENTA, -1);   // Agentes
    init_pair(6, 8, -1);   // Prints

    clear();
    refresh();
    anim_draw_cenario();

    UNLOCK_SCREEN();
}

void anim_close() {
    endwin();
}

void reset_text(sprite *s) {
    for (int i = 0; s->og_text[i] != '\0'; i++) {
        s->text[i] = s->og_text[i];
    }
}

void move_sprite(sprite *s, int x_plus, int y_plus) {
    LOCK_SCREEN();
    // limpa a posição atual do sprite
    for (int i = 0; s->text[i] != '\0'; i++) {
        mvaddch(s->y, s->x + i, ' ');
    }
    
    // atualiza a posição do sprite
    s->x += x_plus;
    s->y += y_plus;
    
    // desenha o sprite na nova posição
    draw_sprite(s);
    
    refresh();
    UNLOCK_SCREEN();
}

void anim_show_sprite(sprite *s) {
    LOCK_SCREEN();
    draw_sprite(s);
    refresh();
    UNLOCK_SCREEN();
}

void draw_sprite(sprite *s) {
    int i = 0;
    // Percorre o texto caractere por caractere até o final
    while (s->text[i] != '\0') {
        // Ativa a cor correspondente àquele caractere
        attron(COLOR_PAIR(s->colors[i]));
        
        // Imprime o caractere na posição y, x + i (andando para a direita)
        mvaddch(s->y, s->x + i, s->text[i]);
        
        // Desativa a cor (boa prática)
        attroff(COLOR_PAIR(s->colors[i]));
        
        i++;
    }
}

void locking_print(int y, int x, const char *str) {
    LOCK_SCREEN();
    mvprintw(y, x, str);
    refresh();
    UNLOCK_SCREEN();
}

void anim_smoking(sprite *s, int time_smoking) {
    s->y0 = s->y;

    while (s->x < 11) {
        move_sprite(s, 1, 0);
        msleep(90);
    }

    while (s->y < 10) {
        move_sprite(s, 0, 1);
        msleep(140);
    }

    while (s->x < 22) {
        move_sprite(s, 1, 0);
        msleep(90);
    }

    while (s->y > 7) {
        move_sprite(s, 0, -1);
        msleep(140);
    }

    // temos a faca e o queijo
    s->text[1] = '\0';

    locking_print(s->y, s->x + 1, "==o");
    msleep(time_smoking * 333);
    locking_print(s->y, s->x + 1, "=o ");
    msleep(time_smoking * 333);
    locking_print(s->y, s->x + 1, "o ");
    msleep(time_smoking * 333);
    locking_print(s->y, s->x + 1, " ");

    msleep(500);

    while (s->y < 10) {
        move_sprite(s, 0, 1);
        msleep(200);
    }

    while (s->x > 11) {
        move_sprite(s, -1, 0);
        msleep(140);
    }
    
    while (s->y > s->y0) {
        move_sprite(s, 0, -1);
        msleep(200);
    }

    while (s->x > 7) {
        move_sprite(s, -1, 0);
        msleep(140);
    }
}

void anim_recharge(sprite *s) {
    reset_text(s);
    anim_show_sprite(s);
}

void anim_agent_1(sprite *s) {
    s->y0 = s->y;
    
    while (s->x > 38) {
        move_sprite(s, -1, 0);
        msleep(140);
    }

    while (s->y < 10) {
        move_sprite(s, 0, 1);
        msleep(200);
    }

    
    while (s->x > 23) {
        move_sprite(s, -1, 0);
        msleep(140);
    }
    
    while (s->y > 7) {
        move_sprite(s, 0, -1);
        msleep(200);
    }

    s->text[1] = '\0';

    while (s->y < 10) {
        move_sprite(s, 0, 1);
        msleep(200);
    }
}

void anim_agent_2(sprite *s) {
    while (s->x < 38) {
        move_sprite(s, 1, 0);
        msleep(140);
    }
    
    while (s->y > s->y0) {
        move_sprite(s, 0, -1);
        msleep(200);
    }

    while (s->x < 42) {
        move_sprite(s, 1, 0);
        msleep(140);
    }

    reset_text(s);
}

void anim_draw_cenario() {
    mvprintw(3, 17,  "SALINHA DO FUMO");
    mvprintw(4, 15,  " __________________ ");
    mvprintw(5, 15,  "|                  |");
    mvprintw(6, 15,  "|                  |");
    mvprintw(7, 15,  "|                  |");
    mvprintw(8, 15,  "|                  |");


    mvprintw(11, 15, "|                  |");
    mvprintw(12, 15, "|__________________|");
    refresh();
}

void anim_print(const char *format, ...) {
    LOCK_SCREEN();
    
    char buffer[256]; 
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    
    if (print_line_count > PRINT_END) {
        print_line_count = PRINT_START;
        for (int i = PRINT_START; i <= PRINT_END; i++) {
            move(i, 5);
            clrtoeol();
        }
    }
    
    move(print_line_count, 5);
    clrtoeol();
    attron(COLOR_PAIR(6));
    mvprintw(print_line_count, 5, "-> %s", buffer);
    attroff(COLOR_PAIR(6));
    
    print_line_count++;
    
    refresh();
    UNLOCK_SCREEN();
}