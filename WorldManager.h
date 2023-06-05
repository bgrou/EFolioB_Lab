#ifndef WORLDMANAGER_H
#define WORLDMANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "RectangleManager.h"

#define INVALID_COORDINATES "Coordenadas Inválidas"

typedef struct {
    char** blocks;
    int l;
    int h;
    List* rectangle_list;
} World;

typedef enum {BORDER = 'x', EMPTY = '.'} BLOCKTYPE;

World* create_world(int l, int h);
char** create_blocks(const int l, const int h);
int check_valid_coordinates(World* world, int x, int y, int l, int h);
void free_world(World *world);
void free_blocks(World* world);
void update_rectangles(World* world);
void perform_move(World* world, Rectangle* rectangle, int p);
Rectangle* get_rectangle_by_pos(World* world, int x, int y);
void draw_rectangle(World* world, Rectangle* rectangle);
void erase_rectangle(World* world, Rectangle* rectangle);
int apply_gravity_rectangle(World* world, Rectangle* rectangle);
int is_unstable_column(World* world, Rectangle* rectangle, int x);
float calculate_rectangle_stability(World* world, Rectangle* rectangle);
float calculate_median_stability(World* world);
void print_instability_alert(float instability_percentage);
#endif
