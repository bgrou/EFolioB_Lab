#include "CommandParser.h"

int execute_command(World* world, char* command_string) {
    char* command = strtok(command_string, " ");
    char* command_params = strtok(NULL, " ");
    int execute_status = 0;
    if(strcmp(command, "create") == 0) {
        execute_status = create_command(world, command_params);
    } else if(strcmp(command, "moveleft") == 0) {
        execute_status = move_command(world, command_params, 0);
    } else if(strcmp(command, "moveright") == 0) {
        execute_status = move_command(world, command_params, 1);
    } else if(strcmp(command, "sair") == 0) {
        execute_status = -1;
    } else{
        printf(INVALID_COMMAND);
    }
    return execute_status;
}

Rectangle* create_and_initialize_rectangle(char* command_params, int world_height) {
    int x, y, l, h;
    x = atoi(strtok(command_params, ",")) - 1;
    y = world_height - atoi(strtok(NULL, "+")) + 2;
    l = atoi(strtok(NULL, ","));
    h = atoi(strtok(NULL, ","));

    return create_rectangle(x, y - h, l, h);
}

int create_command(World* world, char* command_params) {
    Rectangle* rectangle = create_and_initialize_rectangle(command_params, world->h);

    if(rectangle != NULL && check_valid_coordinates(world, rectangle->x, rectangle->y, rectangle->l, rectangle->h)) {
        apply_gravity_rectangle(world, rectangle);
        draw_rectangle(world, rectangle);
        list_push(world->rectangle_list, rectangle);
        return 1;
    }

    printf("Não é possível criar um rectângulo nestas coordenadas.\n");
    return 0;
}

/* Calcula se o movimento do retângulo é válido, verificando as novas coordenadas
** tendo em conta se o movimento é para a esquerda ou para a direita */
int calculate_valid_move(World* world, Rectangle* rectangle, int p) {
    return p > 0 ? check_valid_coordinates(world, rectangle->x + rectangle->l, rectangle->y, p, rectangle->h)
                 : check_valid_coordinates(world, rectangle->x - 1, rectangle->y, p, rectangle->h);
}

int move_command(World* world, char* command_params, int right) {
    int x = atoi(strtok(command_params, ",")) - 1;
    int y = world->h - atoi(strtok(NULL, "+")) + 1;
    int p = (right) ? atoi(strtok(NULL, ",")) : atoi(strtok(NULL, ",")) * -1;
    Rectangle* rectangle = get_rectangle_by_pos(world, x, y);

    if (rectangle == NULL) {
        printf(RECTANGLE_NOT_FOUND);
        return 0;
    }
    if (!calculate_valid_move(world, rectangle, p)) {
        printf(MOVE_COLLIDED);
        return 0;
    }
    perform_move(world, rectangle, p);
    return 1;
}




