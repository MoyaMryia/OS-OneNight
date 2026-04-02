#include "standio.h"

void puts(char *str){
    sendText(str);
}

void putchar(char ch){
    sendChar(ch);
}

char getchar(){
    return (char)getChar();
}

int getline(char *buf, int maxlen){
    int i = 0;
    char ch = 0;
    while(1){
        ch = getchar();
        if(ch == '\r'){
            buf[i] = '\0';
            putchar('\r');
            putchar('\n');
            return i;
        }else if(ch == 0x7f || ch == 0x08){
            if(i > 0){
                --i;
                puts("\b \b");
            }
            continue;
        }else if(i < maxlen - 1){
            buf[i++] = ch;
            putchar(ch);
        }else{
            continue;
        }
    }
}