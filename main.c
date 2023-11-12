#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

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

void read_guess(char *guess) {
    char char_read;
    int i = 0;
    while(read(1, &char_read, 1) && char_read != '\n') {
        if (i < CODE_SIZE) {
            guess[i] = char_read;
            i++;
        }
    }
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
    printf("Well placed pieces: %d\nMisplaced pieces: %d\n", placed, misplaced);
    return placed == CODE_SIZE;
}

void setup_game(char *secret, int *max_guesses, int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        if(strcmp(argv[i], "-c") == 0) {
            if (i + 1 < argc) {
                for (int j = 0; argv[i + 1][j] != '\0'; j++) {
                    if (j < CODE_SIZE) {
                        secret[j] = argv[i + 1][j];
                    }
                }
                if (!check_code_valid(secret)) {
                    printf("Wrong input!\n");
                }
            }
        }
        if (strcmp(argv[i], "-t") == 0) {
            if (i + 1 < argc) {
                *max_guesses = atoi(argv[i + 1]);
            }
        }
    }
}

int main(int argc, char **argv) {
    int max_guesses = DEFAULT_GUESSES;
    int round = 0;
    int valid = 0;
    char *secret = malloc(sizeof(*secret) * (CODE_SIZE + 1));
    char *guess = malloc(sizeof(*guess) * (CODE_SIZE + 1));
    
    setup_game(secret, &max_guesses, argc, argv);
    printf("Recorded secret: %s\n", secret);
    printf("Recorded max guesses: %d\n", max_guesses);

    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    while (round < max_guesses) {
        printf("---\nRound %d\n", round);
        valid = 0;
        while (!valid) {
            read_guess(guess);
            if (!(valid = check_code_valid(guess))) {
                printf("Wrong input!\n");
            }
        }
        //printf("Recorded guess: %s\n", guess);
        if (evaluate(secret, guess)) {
            printf("Congratz! You did it!\n");
            break;
        }
        round++;
    }

    free(secret);
    free(guess);
    return 0;
}