#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CODE_SIZE 4
#define DEFAULT_GUESSES 10

struct game {
    int max_guesses;
    char secret[CODE_SIZE + 1];
    char guess[CODE_SIZE + 1];
    int placed;
    int misplaced;
};

/*
*
* Evaluates whether the provided code is a valid mastermind code.
*
* @param char *code
*
* @return 1 if code is valid, else 0
*
*/
int check_code_valid(char *code) {
    int i = 0;
    while (code[i]) {
        if (code[i] < '0' || code[i] > '8')
            break;
        i++;
    }
    return i == CODE_SIZE;
}

/*
*
* Reads from stdin character by character and puts the first CODE_SIZE
* number of characters into the provided guess buffer.
*
* @param char *guess
*
* @return 1 if character(s) successfully read, 0 on error or EOF
*
*/
int read_from_stdin(char *guess) {
    char char_read;
    int i = 0;
    int bytes_read = 0;
    while((bytes_read = read(0, &char_read, 1)) > 0 && char_read != '\n') {
        if (i < CODE_SIZE) {
            guess[i] = char_read;
            i++;
        }
    }
    printf("%d\n", bytes_read);
    // if bytes_read <= 0 either EOF (crtl + d) encountered (0) or error while reading (-1)
    return bytes_read > 0;
}

/*
*
* Reads code from user input. If no valid code was entered,
* the user is notified and asked to re-enter a code.
*
* @param char *guess
*
* @return 1 if code is valid, 0 if error or EOF encountered while reading
*
*/
int read_guess(char *guess) {
    int valid = 0;
    while (!valid) {
        if (!read_from_stdin(guess)) {
            return 0;
        }
        if (!(valid = check_code_valid(guess))) {
            printf("Wrong input!\n");
        }
    }
    return 1;
}

/*
*
* Compares the guess to the secret code and evaluates the number of
* correctly placed and misplaced digits.
*
* @param char *secret
* @param char *guess
*
* @return 1 if guess == code, else 0
*
*/
int evaluate(char *secret, char *guess) {
    int matched[CODE_SIZE] = {0};
    int placed = 0;
    int misplaced = 0;

    // check for correctly placed
    for(int i = 0; i < CODE_SIZE; i++) {
        if(guess[i] == secret[i]) {
            matched[i] = 1;
            placed++;
        }
    }
    // check for misplaced
    // iterate guess
    for (int i = 0; i < CODE_SIZE; i++) {
        if (guess[i] != secret[i]) {
            // iterate secret
            for (int j = 0; j < CODE_SIZE; j++) {
                if (!matched[j] && guess[i] == secret[j]) {
                    matched[j] = 1;
                    misplaced++;
                    break;
                } 
            }
        }
    }
    return placed == CODE_SIZE;
}

/*
*
* Generate a pseudo-random secret code and writes it to the provided buffer secret.
*
* @param char *secret
*
*/
void generate_random_secret(char *secret) {
    srand(time(NULL));
    int i = 0;
    while (i < CODE_SIZE) {
        secret[i] = rand() % 9 + '0';
        i++;
    }
}

/*
*
* Handles program flags and sets up the mastermind game according to
* the provided user parameters.
*
* @param char *secret
* @param int *max_guesses
* @param int argc
* @param char **argv
*
*/
void setup_game(struct game *mastermind, int argc, char **argv) {
    int max_guesses_input = 0;
    int secret_valid = 0;

    // initialize game state
    // read and handle parameter flags

    for (int i = 1; i < argc; i++) {
        if(strcmp(argv[i], "-c") == 0) {
            if (i + 1 < argc) {
                for (int j = 0; argv[i + 1][j] != '\0'; j++) {
                    if (j < CODE_SIZE) {
                        mastermind->secret[j] = argv[i + 1][j];
                    }
                }
                secret_valid = check_code_valid(mastermind->secret);
                if (!secret_valid) {
                    printf("Secret code is invalid. Random secret code was generated.\n");
                }
            } else {
                printf("No secret code provided. Random secret code was generated.\n");
            }
        }
        if (strcmp(argv[i], "-t") == 0) {
            if (i + 1 < argc) {
                if ((max_guesses_input = atoi(argv[i + 1])) > 0) {
                    *max_guesses = max_guesses_input;
                } else {
                    printf("Number of attempts is invalid. Default of %d is used.\n", DEFAULT_GUESSES);
                }
            } else {
                printf("No number of attempts provided. Default of %d is used.\n", DEFAULT_GUESSES);
            }
        }
    }
    if (!secret_valid) {
        generate_random_secret(mastermind->secret);
    }
}

int play_game(struct game *mastermind) {
    int round = 0;
    int success = 0;

    while (round < mastermind->max_guesses) {
        printf("---\nRound %d\n", round);
        if (!read_guess(mastermind->guess)) {
            return 0;
        }
        success = evaluate(mastermind->secret, mastermind->guess);
        if (success) {
            // solution found
            return 1;
        } else {
            // no solution found in current attempt
            printf("Well placed pieces: %d\nMisplaced pieces: %d\n", mastermind->placed, mastermind->misplaced);
        }
        round++;
    }
    // no solution found after all attempts
    return 0;
}

void initialize_game_state(struct game *mastermind) {
    int i = 0;
    mastermind->max_guesses = DEFAULT_GUESSES;
    while (i < CODE_SIZE + 1) {
        mastermind->guess[i] = '\0';
        mastermind->secret[i] = '\0';
        i++;
    }
    mastermind->placed = 0;
    mastermind->misplaced = 0;
}

int main(int argc, char **argv) {
    struct game mastermind;
    int success = 0;
    
    initialize_game_state(&mastermind);
    setup_game(&mastermind, argc, argv);
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    success = play_game(&mastermind);
    if (success) {
        printf("Congratz! You did it!\n");
    } else {
        reveal_secret(&mastermind);
    }
    return 0;
}