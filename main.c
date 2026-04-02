#include "include/uart.h"
void main(){
    sendText("Testing OS\n");
    while(1){
        char ch = 0;
        ch = getChar();
        if(ch == '\r'){ 
            sendChar('\r');
            sendChar('\n');
        }else{
            sendChar(ch);
        }
    }
}