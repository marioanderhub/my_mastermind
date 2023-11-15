#include <unistd.h>
#include <stdlib.h>
#include <time.h>

/*
*
* Evaluates whether the provided code is a valid mastermind code.
*
* @param char *code
*
* @return 1 if code is valid, else 0
*
*/
int check_code_valid(char *code, int size) {
    int i = 0;
    while (code[i]) {
        if (code[i] < '0' || code[i] > '8')
            break;
        i++;
    }
    return i == size;
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
int read_from_stdin(char *guess, int size) {
    char char_read;
    int i = 0;
    int bytes_read = 0;
    while((bytes_read = read(0, &char_read, 1)) > 0 && char_read != '\n') {
        if (i < size) {
            guess[i] = char_read;
            i++;
        }
    }
    // if bytes_read <= 0 either EOF (crtl + d) encountered (0) or error while reading (-1)
    return bytes_read > 0;
}

/*
*
* Generate a pseudo-random secret code and writes it to the provided buffer secret.
*
* @param char *secret
*
*/
void generate_random_secret(char *secret, int size, int max) {
    srand(time(NULL));
    int i = 0;
    while (i < size) {
        secret[i] = rand() % max + '0';
        i++;
    }
}

/*
*
* Sets n bytes of char buffer str to NUL byte ('\0').
*
* @param char *str
* @param int bytes
*
*/
void set_str_empty(char *str, int n) {
    int i = 0;
    
    while (i < n) {
        str[i] = '\0';
        i++;
    }
}