#include <stdio.h>

#define CODE_SIZE 4

int main(void) {
    char *secret_code = "0123";
    char *user_code = "3122";
    int matched[CODE_SIZE] = {0};
    int placed = 0;
    int misplaced = 0;

    // check for correctly placed
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
    printf("placed: %d, misplaced: %d", placed, misplaced);
    return 0;
}