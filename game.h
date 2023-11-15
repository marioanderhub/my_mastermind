#ifndef GAME_H
#define GAME_H

#define CODE_SIZE 4
#define DEFAULT_GUESSES 10

typedef struct {
    int max_guesses;
    char secret[CODE_SIZE + 1];
    char guess[CODE_SIZE + 1];
    int placed;
    int misplaced;
} game;

void initialize_game(game *mastermind);
void handle_c_flag(game *mastermind, int argc, char **argv, int i);
void handle_t_flag(game *mastermind, int argc, char **argv, int i);
void setup_game(game *mastermind, int argc, char **argv);
int read_guess(char *guess);
int evaluate(game *mastermind);
void play_game(game *mastermind);

#endif //GAME_H