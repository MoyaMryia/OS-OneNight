void main(){
    volatile char *uart = (volatile char*)0x10000000;
    *uart = 'H';
    *uart = 'e';
    *uart = 'l';
    *uart = 'l';
    *uart = 'o';
    while(1){

    }
}