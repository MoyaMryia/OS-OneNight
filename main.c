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

void main(){
    sendChar('H');
    sendChar('e');
    sendChar('l');
    sendChar('l');
    sendChar('o');
    sendChar('\n');
    while(1){

    }
}