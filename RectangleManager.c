#include "RectangleManager.h"

Rectangle* create_rectangle(int x, int y, int l, int h) {
    Rectangle *rectangle = malloc(sizeof (Rectangle));
    rectangle->x = x;
    rectangle->y = y;
    rectangle->l = l;
    rectangle->h = h;
    return rectangle;
}

void free_rectangle(Rectangle * rectangle) {
    free(rectangle);
}

List* create_rectangle_list() {
    return list_create((CallbackFree) free_rectangle, sizeof(Rectangle));
}

void move_rectangle(Rectangle* rectangle, int p) {
    rectangle->x += p;
}

