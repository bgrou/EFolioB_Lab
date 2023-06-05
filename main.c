#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "CommandParser.h"
#include "WorldManager.h"
#define INPUT_COMMAND "Introduza o comando pretendido: "
#define EXITING_PROGRAM "A encerrar programa..."

void show_menu() {
    printf("\n");
    printf("=================================================\n");
    printf("=                      Menu                     =\n");
    printf("=================================================\n");
    printf("= create x,y+l,h                                =\n");
    printf("= moveleft x,y+p                                =\n");
    printf("= moveleft x,y+p                                =\n");
    printf("= sair                                          =\n");
    printf("=================================================\n");
}

char* get_input() {
    char* input = (char*)malloc(50 * sizeof(char));
    printf(INPUT_COMMAND);
    fgets(input, 50, stdin);
    input[strcspn(input, "\n")] = 0;
    return input;
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    int execute_status = 0;
    World *world = create_world(80, 25);
    while (execute_status != -1) {
        show_menu();
        char *command_str = get_input();
        printf("\n");
        execute_status = execute_command(world, command_str);
        //Se o utilizador executar o comando "sair" o execute_status será -1
        if(execute_status == 1) {
            draw_world(world);
            print_instability_alert(calculate_median_stability(world));
        }
    }
    printf(EXITING_PROGRAM);
    free_world(world);
    return 0;
}
