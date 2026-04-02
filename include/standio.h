#ifndef STANDIO
#define STANDIO
#include "uart.h"

void putchar(char ch);
void puts(char *str);
char getchar();
int getline(char *buf, int maxlen);

#endif