#ifndef UTILS_H
#define UTILS_H

int check_code_valid(char *code, int size);
int read_from_stdin(char *guess, int size);
void generate_random_secret(char *secret, int size, int max);
void set_str_empty(char *str, int n);

#endif //UTILS_H