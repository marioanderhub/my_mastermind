#ifndef GAME_H
#define GAME_H

#define CODE_SIZE 4
#define DEFAULT_GUESSES 10

struct game {
    int max_guesses;
    char secret[CODE_SIZE + 1];
    char guess[CODE_SIZE + 1];
    int placed;
    int misplaced;
};


void initialize_game(struct game *mastermind);
void play_game(struct game *mastermind);
int read_guess(char *guess);
int evaluate(struct game *mastermind);
void setup_game(struct game *mastermind, int argc, char **argv);

#endif //GAME_H