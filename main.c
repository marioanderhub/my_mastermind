#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CODE_SIZE 4
#define DEFAULT_GUESSES 10

int check_code_valid(char *code) {
    int i = 0;
    while (code[i]) {
        if (code[i] < '0' || code[i] > '8')
            break;
        i++;
    }
    if (i < CODE_SIZE) {
        // code invalid
        return 0;
    }
    else {
        // code valid
        return 1;
    }
}

int read_guess(char *guess) {
    char char_read;
    int i = 0;
    int bytes_read = 0;
    while((bytes_read = read(0, &char_read, 1)) > 0 && char_read != '\n') {
        if (i < CODE_SIZE) {
            guess[i] = char_read;
            i++;
        }
    }
    // if bytes_read <= 0 either EOF reached resp. crtl + d encountered (0) or error while reading (-1)
    // TODO: function should only return whether error or eof occurred while reading, all checking validity of code should happen in check_code_valid
    return bytes_read > 0;
}

int evaluate(char *secret_code, char *user_code) {
    int matched[CODE_SIZE] = {0};
    int placed = 0;
    int misplaced = 0;

    // check for correctly placed
    // iterate user_code and secret_code together
    for(int i = 0; i < CODE_SIZE; i++) {
        if(user_code[i] == secret_code[i]) {
            matched[i] = 1;
            placed++;
        }
    }
    // check for misplaced
    // iterate user_code
    for (int i = 0; i < CODE_SIZE; i++) {
        if (user_code[i] != secret_code[i]) {
            // iterate secret_code
            for (int j = 0; j < CODE_SIZE; j++) {
                if (!matched[j] && user_code[i] == secret_code[j]) {
                    matched[j] = 1;
                    misplaced++;
                    break;
                } 
            }
        }
    }
    if (placed == CODE_SIZE) {
        printf("Congratz! You did it!\n");
        return 1;
    } else {
        printf("Well placed pieces: %d\nMisplaced pieces: %d\n", placed, misplaced);
        return 0;
    }
}

void generate_random_secret(char *secret) {
    srand(time(NULL));
    int i = 0;
    while (i < CODE_SIZE) {
        secret[i] = rand() % 9 + '0';
        i++;
    }
}

// TODO: simplify? error handling?
void setup_game(char *secret, int *max_guesses, int argc, char **argv) {
    int max_guesses_input = 0;
    int secret_valid = 0;

    for (int i = 1; i < argc; i++) {
        if(strcmp(argv[i], "-c") == 0) {
            if (i + 1 < argc) {
                for (int j = 0; argv[i + 1][j] != '\0'; j++) {
                    if (j < CODE_SIZE) {
                        secret[j] = argv[i + 1][j];
                    }
                }
                secret_valid = check_code_valid(secret);
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
        generate_random_secret(secret);
    }
}

int main(int argc, char **argv) {
    int max_guesses = DEFAULT_GUESSES;
    int round = 0;
    int valid = 0;
    // opting for fixed-size arrays instead of dynamic memory allocation, bc array size known at compile time
    // and lifetime of array is limited to main() and its subfunctions.
    char secret[CODE_SIZE + 1] = {'\0'};
    char guess[CODE_SIZE + 1] = {'\0'};
    /*
    char *secret = malloc(sizeof(*secret) * (CODE_SIZE + 1));
    char *guess = malloc(sizeof(*guess) * (CODE_SIZE + 1));
    */
    
    setup_game(secret, &max_guesses, argc, argv);
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    while (round < max_guesses) {
        printf("---\nRound %d\n", round);
        // TODO: outsource
        valid = 0;
        while (!valid) {
            if (!read_guess(guess)) {
                /*
                free(secret);
                free(guess);
                */
                return 0;
            }
            if (!(valid = check_code_valid(guess))) {
                printf("Wrong input!\n");
            }
        }
        //
        if (evaluate(secret, guess)) {
            break;
        }
        round++;
    }
    /*
    free(secret);
    free(guess);
    */
    return 0;
}