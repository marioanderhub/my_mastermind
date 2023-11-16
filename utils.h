#ifndef UTILS_H
#define UTILS_H

int check_str_valid(char *str, int size, char min, char max);
int read_from_stdin(char *buf, int n);
void generate_random_secret(char *buf, int n, int max);
void set_str_empty(char *str, int n);

#endif //UTILS_H