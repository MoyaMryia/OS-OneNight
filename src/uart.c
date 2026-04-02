#include "uart.h"

int sendSingleChar(char ch) {
    if ((*UART_REG(UART_LSR) & LSR_TX_IDLE) != 0) {
        *UART_REG(UART_THR) = ch;
        return 0;
    } else {
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

