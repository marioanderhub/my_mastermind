#include "game.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    game mastermind;
    
    initialize_game(&mastermind);
    setup_game(&mastermind, argc, argv);
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    play_game(&mastermind);
    return EXIT_SUCCESS;
}