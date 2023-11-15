#include "utils.h"
#include "game.h"
#include <stdio.h>

int main(int argc, char **argv) {
    struct game mastermind;
    
    initialize_game(&mastermind);
    setup_game(&mastermind, argc, argv);
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    play_game(&mastermind);
    return 0;
}