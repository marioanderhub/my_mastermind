#include "game.h"
#include <stdlib.h>

int main(int argc, char **argv) {
    game mastermind;
    
    initialize_game(&mastermind);
    setup_game(&mastermind, argc, argv);
    play_game(&mastermind);
    return EXIT_SUCCESS;
}