#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

char *decrypt(const char *str, int key);
char *encrypt(const char *str, int key);
void update_balance(const char *uname, const char *password, int amount);
int check_user(const char *uname, const char *password);
int get_balance(const char *uname, const char *password);
