#include "WorldManager.h"

/* Cria um mundo com base nos tamanhos fornecidos.
** A função retorna uma estrutura de mundo com a largura e altura especificadas,
** blocos inicializados como vazios e uma lista vazia de retângulos. */
World* create_world(const int l, const int h) {
    World* world = (World*)malloc(sizeof(World));
    world->blocks = create_blocks(l, h);
    world->l = l;
    world->h = h;
    world->rectangle_list = create_rectangle_list();
    return world;
}

/* Cria uma matriz de blocos com base nos tamanhos fornecidos.
** A função aloca uma matriz dinâmica de blocos e inicializa todos os blocos como vazios. */
char** create_blocks(const int l, const int h) {
    char** blocks = (char**)malloc(h * sizeof(char*));
    for(int i = 0; i < h; i++) {
        blocks[i] = (char*)malloc(l * sizeof(char));
        for(int j = 0; j < l; j++) {
            blocks[i][j] = EMPTY;  // inicializa todos os elementos como espaço vazio
        }
    }
    return blocks;
}

/* Liberta a memória alocada para os blocos.
** Percorre os blocos do mundo na ordem inversa da criação,
** libertando cada linha individualmente antes de libertar o array principal de ponteiros. */
void free_blocks(World* world) {
    for(int i = 0; i < world->h; i++) {
        free(world->blocks[i]);
    }
    free(world->blocks);
}

int has_rectangle_at_position(World* world, int x, int y) {
    return get_rectangle_by_pos(world, x, y) != NULL;
}

int is_out_of_world_bounds(World* world, int x, int y) {
    return x < 0 || x >= world->l || y < 0 || y >= world->h;
}

/* Verifica se as coordenadas fornecidas são válidas.
** Retorna 1 se todas as coordenadas forem válidas e não houver retângulos
** a ocupar as posições, caso contrário retorna 0. */
int check_valid_coordinates(World* world, int x, int y, int l, int h) {
    int stepX = (l > 0) ? 1 : -1;
    if (l == 0 || h == 0) {
        printf(INVALID_COORDINATES);
        return 0;
    }
    // A condição de continuação do loop (stepX > 0) ? i < x + l : i > x + l
    // permite que ele funcione tanto para movimentos para a direita (quando stepX > 0)
    // como para a esquerda (quando stepX < 0).
    for (int i = x; (stepX > 0) ? i < x + l : i > x + l; i += stepX) {
        for (int j = y; j < y + h - 1; j++) {
            if (is_out_of_world_bounds(world, i, j) || has_rectangle_at_position(world, i, j)) {
                printf(INVALID_COORDINATES);
                return 0;  // As coordenadas são inválidas ou já existem retângulos ocupando as posições
            }
        }
    }
    return 1;  // Todas as coordenadas são válidas e não há retângulos a ocupar as posições
}

/* Verifica se um retângulo está assente.
** Retorna 1 se o retângulo estiver assente, caso contrário retorna 0. */
int is_rectangle_settled(World* world, Rectangle* rectangle) {
    for(int i = rectangle->x - 1; i < rectangle->x + rectangle->l - 1; i++) {
        //
        if( rectangle->y + rectangle->h - 1 == world->h || world->blocks[rectangle->y + rectangle->h - 1][i] == BORDER) {
            return 1;
        }
    }
    return 0;
}

/* Aplica a gravidade a um retângulo.
** Retorna 1 se a operação for bem-sucedida, caso contrário retorna 0. */
int apply_gravity_rectangle(World* world, Rectangle* rectangle) {
    if(rectangle != NULL) {
        while(!is_rectangle_settled(world, rectangle)) {
            rectangle->y++;
        }
        return 1;
    }
    return 0;
}

/* Retorna o retângulo localizado na posição fornecida.
** Se não houver retângulo na posição fornecida, retorna NULL. */
Rectangle* get_rectangle_by_pos(World* world, int x, int y) {
    Rectangle* rectangle = NULL;
    for (Node* current_node = world->rectangle_list->head; current_node != NULL; current_node = current_node->next) {
        rectangle = current_node->data;
        //Verifica se a coordenada de (x,y) pertence ao rectângulo atual
        if((x >= rectangle->x && x < rectangle->x + rectangle->l) && y >= rectangle->y && y < rectangle->y + rectangle->h) {
            return rectangle;
        }
    }
    return NULL;
}

/* Realiza a movimentação de um retângulo, atualizando a sua posição
** e a dos outros retângulos no mundo. */
void perform_move(World* world, Rectangle* rectangle, int p) {
    erase_rectangle(world, rectangle);
    move_rectangle(rectangle, p);
    apply_gravity_rectangle(world, rectangle);
    draw_rectangle(world, rectangle);
    update_rectangles(world);
}

/* Atualiza a posição de todos os retângulos no mundo,
** aplicando a gravidade e redesenhando-os. */
void update_rectangles(World* world) {
    for (Node* current_node = world->rectangle_list->head; current_node != NULL; current_node = current_node->next) {
        Rectangle* rect = current_node->data;
        erase_rectangle(world, rect);
        apply_gravity_rectangle(world, rect);
        draw_rectangle(world, rect);
    }
}

int is_unstable_column(World* world, Rectangle* rectangle, int x) {
    return rectangle->y + rectangle->h - 1 != world->h  && world->blocks[rectangle->y + rectangle->h - 1][x] != BORDER;
}

/* Calcula a percentagem de instabilidade de um rectângulo */
float calculate_rectangle_stability(World* world, Rectangle* rectangle) {
    int instable_cols = 0;
    float instability_percentage;
    // Verifica cada coluna do retângulo para instabilidade
    for (int i = rectangle->x; i < rectangle->x + rectangle->l; i++) {
        // Se a coluna está fora do mundo ou não está sobre a borda, incrementa o contador de colunas instáveis
        if(is_unstable_column(world, rectangle, i)){
            instable_cols++;
        }
    }
    // Calcula a porcentagem de instabilidade
    instability_percentage = (float)instable_cols / (float)rectangle->l * 100;
    return instability_percentage;
}

/* Calcula a percentagem média de instabilidade dos rectângulos do mundo*/
float calculate_median_stability(World* world) {
    int unstable_rect_count = 0;
    float total_instability = 0.0f;

    for (Node* current_node = world->rectangle_list->head; current_node != NULL; current_node = current_node->next) {
        Rectangle* rectangle = current_node->data;
        float rectangle_instability = calculate_rectangle_stability(world, rectangle);

        if (rectangle_instability > 50.0f) {
            total_instability += rectangle_instability;
            unstable_rect_count++;
        }
    }
    return (unstable_rect_count > 0) ? total_instability / (float)unstable_rect_count : 0.0f;
}

/* Alerta de instabilidade se a percentagem média de instabilidade
** do mundo for superior a 70%*/
void print_instability_alert(float instability_percentage) {
    if(instability_percentage >= 70.0f) {
        printf("ALERTA!!! A instabilidade do sistema é: %.2f %%\n", instability_percentage);
    }
}

/* Libertar memória do objeto world*/
void free_world(World *world) {
    list_destroy(world->rectangle_list);
    free_blocks(world);
    free(world);
}




