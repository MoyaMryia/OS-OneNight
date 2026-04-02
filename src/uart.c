#include "uart.h"

int sendSingleChar(char ch){
    volatile char *uart = (volatile char*)0x10000000;
    volatile char *chk = (volatile char*)0x10000005;
    if((*chk & 0x20) != 0){
        *uart = ch;
        return 0;
    }else{
        return 1;
    }
}

void sendChar(char ch){
    while(sendSingleChar(ch)!=0);
}

void sendText_f(char *str, unsigned int str_len){
    for(int i = 0; i < str_len; ++i){
        sendChar(*(str+i));
    }
}

void sendText(char *str){
    int i = 0;
    while(*(str+i)){
        sendChar(*(str+i));
        ++i;
    }
}

void puts(char *str){
    sendText(str);
}

void putchar(char ch){
    sendChar(ch);
}

int getSingleChar(){
    if(((*UART_REG(UART_LSR)) & LSR_RX_READY)!=0){
        return (int)(*UART_REG(UART_RHR));
    }
    return -1;
}

char getChar(){
    int ch = 0;
    while((ch = getSingleChar())== -1){
        
    }
    return (char)ch;
}

int getLine(char *buf, int maxlen){
    int i = 0;
    char ch = 0;
    while(1){
        ch = getChar();
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