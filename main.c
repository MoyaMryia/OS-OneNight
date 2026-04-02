#include "include/standio.h"
void main(){
    puts("WOZMON 2026 on RISC-V.\n");
    puts("READY.\n");
    char buf[64];char num[64];char addr_num[64];
    unsigned long addr;
    unsigned char val;
    int segment = 0;
    while(1){
        getline(buf,64);
        if(segment == 0){
            addr = hextoNum(buf);
            if(addr != -1){
                val = *(unsigned char*)addr;
                puts(buf);
                putchar(':');
                numToHex(val,num);
                puts(num);
                putchar('\n');
                segment = 1;
            }else{
                puts("ERROR\n");
                segment = 0;
            }
        }else{
            if(buf[0] == '\0' || buf[0] == '\r' || buf[0] == '\n'){
                ++addr;
                val = *(unsigned char*)addr;
                numToHex(addr,addr_num);
                puts(addr_num);
                putchar(':');
                numToHex(val,num);
                puts(num);
                putchar('\n');
                segment = 1;
            }else{
                addr = hextoNum(buf);
                if(addr != -1){
                    val = *(unsigned char*)addr;
                    puts(buf);
                    putchar(':');
                    numToHex(val,num);
                    puts(num);
                    putchar('\n');
                    segment = 1;
                }else{
                    puts("ERROR\n");
                    segment = 0;
                }
            }
        }
        for(int i = 0;i<64;++i){
            buf[i] = 0;
        }
    }
}