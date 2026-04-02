#include "include/standio.h"
void main(){
    char line_buf[64];
    
    while(1){
        getline(line_buf, 64);
        puts("You Typed:\n");
        puts(line_buf);
        putchar('\n');
    }
}