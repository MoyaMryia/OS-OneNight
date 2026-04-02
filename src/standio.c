#include "standio.h"

void putchar(char ch){
    sendChar(ch);
}
void puts(char *str){
    sendText(str);
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
            buf[maxlen - 1] = '\0'; //我不知道什么时候我会把这个给冲了 先这么写
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

char sigtoHex(int num){
    if(num > 15) return 0;
    else{
        if(num < 10){
            return num + '0';
        }else{
            return num - 10 + 'A';
        }
    } 
}

void numToHex(unsigned int num, char *out_buf){ 
    for(int i = 0; i < 8 ;++i){
        out_buf[7-i] = sigtoHex(num & 0xF);
        num >>= 4;
    }
    out_buf[8] = '\0';
}

int hextoSig(char ch){
    if(ch >= '0' && ch <= '9'){
        return (int)(ch - '0');
    }else if(ch >= 'a' && ch <= 'f'){
        return (int)(ch - 'a' + 10);
    }else if(ch >= 'A' && ch <= 'F'){
        return (int)(ch - 'A' + 10);
    }else{
        return -1;
    }
}

unsigned long hextoNum(char *str){
    unsigned long num = 0;
    int i = 0;
    if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) {
        i = 2;
    }
    while(*(str+i) != 0){
        if(*(str+i) == 'X'){
            continue;
        }else if(hextoSig(*(str+i)) == -1){
            return -1;
        }else{
            num = (num << 4) + (hextoSig(*(str+i))&0xF);
        }
        ++i;
    }
    return num;
}