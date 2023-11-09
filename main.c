#include <stdio.h>
#include <unistd.h>

#define CODE_SIZE 4

void evaluate(char *secret_code, char *user_code) {
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
    printf("placed: %d, misplaced: %d", placed, misplaced);
}

int main(void) {
    char secret_code[5] = {'0', '1', '1', '3', '\0'};
    char user_code[5] = {'\0'};
    char char_read;
    int index = 0;
    int invalid = 0;
    while(read(1, &char_read, 1) && char_read != '\n') {
        if (index < CODE_SIZE) {
            if (char_read < '0' || char_read > '8') {
                invalid = 1;
            }
            user_code[index] = char_read;
            index++;
        }
    }
    if (invalid || index < CODE_SIZE) {
        printf("Invalid input\n");
    }
    printf("recorded input: %s\n", user_code);
    evaluate(secret_code, user_code);
    return 0;
}