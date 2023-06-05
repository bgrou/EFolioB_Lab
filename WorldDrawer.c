#include "WorldDrawer.h"

/* Mostra ao utilizador o estado atual do mundo*/
void draw_world(World* world) {
    for(int i = 0; i < world->h; i++) {
        for(int j = 0; j < world->l; j++) {
            printf("%c",world->blocks[i][j]);
        }
        printf("\n");
    }
}

/* Insere nos blocos do mundo os rectângulos que foram criados pelo utilizador*/
void draw_rectangle(World* world, Rectangle* rectangle) {
    //Y borders
    for(int i = rectangle->y - 1; i < rectangle->y + rectangle->h - 1; i++) {
        world->blocks[i][rectangle->x] = BORDER;
        world->blocks[i][rectangle->x + rectangle->l - 1] = BORDER;
    }
    //X borders
    for(int j = rectangle->x; j < rectangle->x + rectangle->l; j++) {
        world->blocks[rectangle->y - 1][j] = BORDER;
        world->blocks[rectangle->y + rectangle->h - 2][j] = BORDER;
    }
}

/* Apaga os rectângulos dos blocos do mundo*/
void erase_rectangle(World* world, Rectangle* rectangle) {
    //Bordas Y
    for(int i = rectangle->y - 1; i < rectangle->y + rectangle->h - 1; i++) {
        world->blocks[i][rectangle->x] = EMPTY;
        world->blocks[i][rectangle->x + rectangle->l - 1] = EMPTY;
    }
    //Bordas X
    for(int j = rectangle->x; j < rectangle->x + rectangle->l; j++) {
        world->blocks[rectangle->y - 1][j] = EMPTY;
        world->blocks[rectangle->y + rectangle->h - 2][j] = EMPTY;
    }
}