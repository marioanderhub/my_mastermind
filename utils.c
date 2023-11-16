#include <unistd.h>
#include <stdlib.h>
#include <time.h>

/*
*
* Evaluates whether the provided string is of length size
* and only consists of ascii characters between min and max (both inclusive).
*
* @param char *str
*
* @return 1 if requirements are met, else 0
*
*/
int check_str_valid(char *str, int size, char min, char max) {
    int i = 0;
    while (str[i]) {
        if (str[i] < min || str[i] > max)
            break;
        i++;
    }
    return i == size;
}

/*
*
* Reads from stdin character by character and puts the first n
* characters into the provided buffer.
*
* @param char *buf
*
* @return 1 if character(s) successfully read, 0 on error or EOF
*
*/
int read_from_stdin(char *buf, int n) {
    char char_read;
    int i = 0;
    int bytes_read = 0;
    while((bytes_read = read(0, &char_read, 1)) > 0 && char_read != '\n') {
        if (i < n) {
            buf[i] = char_read;
            i++;
        }
    }
    return bytes_read > 0;
}

/*
*
* Generate a pseudo-random sequence of n char digits and writes them to the provided buffer.
* Chars can have value from '0' to max (exclusive).
*
* @param char *buf
*
*/
void generate_random_secret(char *buf, int n, int max) {
    srand(time(NULL));
    int i = 0;
    while (i < n) {
        buf[i] = rand() % max + '0';
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