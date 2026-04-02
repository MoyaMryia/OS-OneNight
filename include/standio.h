#ifndef STANDIO_H
#define STANDIO_H
#include "uart.h"

void putchar(char ch);
void puts(char *str);
char getchar();
int getline(char *buf, int maxlen);
void numToHex(unsigned int num, char *out_buf);
char sigtoHex(int num);
int hextoSig(char ch);
unsigned long hextoNum(char *str);
#endif