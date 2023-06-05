#ifndef RECTANGLEMANAGER_H
#define RECTANGLEMANAGER_H

#include <stdlib.h>
#include "LinkedList.h"

typedef struct {
    int x, y, l, h;
} Rectangle;

Rectangle* create_rectangle(int x, int y, int l, int h);
void free_rectangle(Rectangle * rectangle);
void move_rectangle(Rectangle* rectangle, int p);
List* create_rectangle_list();
#endif
