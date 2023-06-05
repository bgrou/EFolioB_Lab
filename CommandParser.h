#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

#include <string.h>
#include "WorldManager.h"
#include "RectangleManager.h"
#include "LinkedList.h"
#include "WorldDrawer.h"

#define INVALID_COMMAND "Comando Inválido! Use apenas os comandos create x,y+l,h | moveright x,y+p | moveleft x,y+p\n"
#define MOVE_COLLIDED "Movimento Inválido! O rectângulo colide com outros rectângulos ou com as bordas do mundo\n"
#define RECTANGLE_NOT_FOUND "Movimento Inválido! Rectângulo não encontrado\n"

int execute_command(World* world, char* command_string);
int create_command(World* world, char* command_params);
int move_command(World* world, char* command_params, int right);
Rectangle* create_and_initialize_rectangle(char* command_params, int world_height);
int calculate_valid_move(World* world, Rectangle* rectangle, int p);

#endif
