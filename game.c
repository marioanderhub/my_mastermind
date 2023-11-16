#include "utils.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
*
* Initializes the struct that contains the game state.
*
* @param game *mastermind
*
*/
void initialize_game(game *mastermind) {
    mastermind->max_guesses = DEFAULT_GUESSES;
    set_str_empty(mastermind->secret, CODE_SIZE + 1);
    set_str_empty(mastermind->guess, CODE_SIZE + 1);
    mastermind->placed = 0;
    mastermind->misplaced = 0;
}

/*
*
* Assigns the user submitted code to the mastermind game state.
* Notifies user of wrong use of -c option or invalid code.
*
* @param game *mastermind
* @param int argc
* @param char **argv
* @param int i
*
*/
void handle_c_flag(game *mastermind, int argc, char **argv, int i) {
    if (i + 1 < argc) {
        for (int j = 0; argv[i + 1][j] != '\0'; j++) {
            if (j < CODE_SIZE) {
                mastermind->secret[j] = argv[i + 1][j];
            }
        }
        if (!check_str_valid(mastermind->secret, CODE_SIZE, '0', '8')) {
            printf("Secret code is invalid. Random secret code was generated.\n");
        }
    } else {
        printf("Option -c requires an argument, but none was provided. Random secret code was generated.\n");
    }
}

/*
*
* Assigns the user submitted number of attempts to the mastermind game state.
* Notifies user of wrong use of -t option or invalid number of attempts.
*
* @param game *mastermind
* @param int argc
* @param char **argv
* int i
*
*/
void handle_t_flag(game *mastermind, int argc, char **argv, int i) {
    int max_guesses_input = 0;
    if (i + 1 < argc) {
        max_guesses_input = atoi(argv[i + 1]);
        if (max_guesses_input > 0) {
            mastermind->max_guesses = max_guesses_input;
        } else {
            printf("Number of attempts is invalid. Default of %d is used.\n", DEFAULT_GUESSES);
        }
    } else {
        printf("Option -t requires an argument, but none was provided. The default of attempts %d attempts was set.\n", DEFAULT_GUESSES);
    }
}

/*
*
* Handles program options -c and -t and sets up the mastermind game
* according to the provided user parameters.
* If no or no valid secret code was provided, a random code is generated.
*
* @param game *mastermind
* @param int argc
* @param char **argv
*
*/
void setup_game(game *mastermind, int argc, char **argv) {

    for (int i = 1; i < argc; i++) {
        if(strcmp(argv[i], "-c") == 0) {
            handle_c_flag(mastermind, argc, argv, i);
        }
        if (strcmp(argv[i], "-t") == 0) {
            handle_t_flag(mastermind, argc, argv, i);
        }
    }
    if (!check_str_valid(mastermind->secret, CODE_SIZE, '0', '8')) {
        generate_random_secret(mastermind->secret, CODE_SIZE, 9);
    }
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
    int bytes_read = 0;

    while (!valid) {
        bytes_read = read_from_stdin(guess, CODE_SIZE);
        if (bytes_read == -1) {
            return 0;
        }
        if(check_str_valid(guess, CODE_SIZE, '0', '8') && bytes_read == CODE_SIZE) {
            valid = 1;
        } else {
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
* Fist loop checks for correctly placed, second loop checks for misplaced.
*
* @param game *mastermind
*
* @return 1 if guess == code, else 0
*
*/
int evaluate(game *mastermind) {
    int matched[CODE_SIZE] = {0};
    int i = 0;
    int j = 0;

    mastermind->placed = 0;
    mastermind->misplaced = 0;
    while (i < CODE_SIZE) {
        if(mastermind->guess[i] == mastermind->secret[i]) {
            matched[i] = 1;
            mastermind->placed++;
        }
        i++;
    }
    i = 0;
    while (i < CODE_SIZE) {
        if (mastermind->guess[i] != mastermind->secret[i]) {
            j = 0;
            while (j < CODE_SIZE) {
                if (!matched[j] && mastermind->guess[i] == mastermind->secret[j]) {
                    matched[j] = 1;
                    mastermind->misplaced++;
                    break;
                }
                j++;
            }
        }
        i++;
    }
    return mastermind->placed == CODE_SIZE;
}

/*
*
* This function performs the game loop:
* Informs user about the game state and asks user to provide guesses.
* The function aborts if an error occurs while reading or an EOF is read.
*
* @param game *mastermind
*
*/
void play_game(game *mastermind) {
    int round = 0;

    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    while (round < mastermind->max_guesses) {
        printf("---\nRound %d\n", round);
        set_str_empty(mastermind->guess, CODE_SIZE + 1);
        if (!read_guess(mastermind->guess)) {
            return;
        }
        if (evaluate(mastermind)) {
            printf("Congratz! You did it!\n");
            return;
        } else {
            printf("Well placed pieces: %d\nMisplaced pieces: %d\n", mastermind->placed, mastermind->misplaced);
        }
        round++;
    }
    printf("GAME OVER! The secret code is: %s\n", mastermind->secret);
}