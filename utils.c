#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/*
*
* Evaluates whether the provided string is of length n
* and only consists of ascii characters between min and max (both inclusive).
*
* @param char *str
* @param int n
* @param char min
* @param max
*
* @return 1 if requirements are met, else 0
*
*/
int check_str_valid(char *str, int n, char min, char max) {
    int i = 0;
    while (str[i]) {
        if (str[i] < min || str[i] > max)
            break;
        i++;
    }
    return i == n;
}

/*
*
* Reads from stdin character by character and puts the first n
* characters into the provided buffer. Reads until newline is reached.
*
* @param char *buf
* @param int n
*
* @return number of total bytes read before newline is encountered; -1 on error or EOF
*
*/
int read_from_stdin(char *buf, int n) {
    char char_read = '\0';
    int bytes_read = 0;
    int total_bytes_read = 0;
    while(1) {
        bytes_read = read(0, &char_read, 1);
        if (bytes_read <= 0) {
            return -1;
        }
        if (char_read == '\n') {
            break;
        }
        if (total_bytes_read < n) {
            buf[total_bytes_read] = char_read;
        }
        total_bytes_read++;
    }
    return total_bytes_read;
}

/*
*
* Generate a pseudo-random sequence of n char digits and writes them to the provided buffer.
* Char digits from 0 to max (exclusive).
*
* @param char *buf
* @param int n
* @param int max
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
* @param int n
*
*/
void set_str_empty(char *str, int n) {
    int i = 0;
    
    while (i < n) {
        str[i] = '\0';
        i++;
    }
}