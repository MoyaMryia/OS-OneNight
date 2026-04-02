#include "include/standio.h"
void main(){
    puts("WOZMON 2026 on RISC-V.\n");
    char buf[64]; char hex_buf[64];
    unsigned long addr = 0;
    int first_run = 1;
    while(1){
        putchar('\\');
        getline(buf, 64);
        char *midpoint = 0;
        char *writepoint = 0;
        int findf = 0;
        for(int i = 0; buf[i]!='\0';++i){
            if(buf[i+1] == '\0' && (buf[i] == 'R' || buf[i] == 'r')){
                findf = 1;
                break;
            }
        }
        for(int i = 0; buf[i]!='\0';++i){
            if(buf[i] == '.'){
                midpoint = buf + i + 1;
                buf[i] = '\0';
            }
            if(buf[i] == ':'){
                writepoint = buf + i + 1;
                buf[i] = '\0';
            }
        }
        if(midpoint == 0 && findf == 0 && writepoint == 0){
            if(buf[0] == '\0' && !first_run){
                addr = addr + 4;
            } else {
                unsigned long new_addr = hextoNum(buf);
                if(new_addr == -1) {
                    puts("ERR\n");
                    continue;
                }
                addr = new_addr;
                first_run = 0;
            }
            unsigned int val = *(unsigned int*)addr;
            numToHex(addr, hex_buf);
            puts(hex_buf);
            putchar(':');
            putchar(' ');
            numToHex(val, hex_buf);
            puts(hex_buf); 
            putchar('\n');
        }else if(midpoint != 0 && findf == 0&& writepoint == 0){
            unsigned long start = 0, end = 0;
            start = hextoNum(buf);
            end = hextoNum(midpoint);
            if(start == -1 || end == -1 || end < start){
                puts("ERR\n");
                continue;
            }
            for(int i = 0; i<=((end-start)>>2); ++i){
                if(i % 4 == 0){
                    putchar('\n');
                    numToHex(i*4+start, hex_buf);
                    puts(hex_buf); 
                    putchar(':');
                }
                unsigned int val = *(unsigned int*)(start+i*4);
                numToHex(val, hex_buf);
                puts(hex_buf); 
                putchar(' ');
            }
            putchar('\n');
        }else if(findf == 1 && writepoint == 0){
            int len = 0;
            while(buf[len] != '\0') len++;
            if(len > 0) buf[len-1] = '\0';
            unsigned long target = hextoNum(buf);
            if(target != (unsigned long)-1){
                puts("RUNNING...\n");
                void (*run_ptr)() = (void (*)())target;
                run_ptr();
                puts("\nBACK TO WOZMON.\n");
            } else {
                puts("RUN ADDR ERR\n");
            }
        }else if (findf == 0 && writepoint != 0){
            unsigned long w_addr = hextoNum(buf);
            unsigned int  w_val  = (unsigned int)hextoNum(writepoint);
            if (w_addr != (unsigned long)-1 && w_val != (unsigned int)-1) {
                unsigned int *p = (unsigned int *)(w_addr & ~3L);
                *p = w_val;
                puts("STORED ");
                numToHex((unsigned long)p, hex_buf);
                puts(hex_buf);
                puts(" = ");
                numToHex(w_val, hex_buf);
                puts(hex_buf);
                putchar('\n');
                addr = (unsigned long)p;
                first_run = 0;
            } else {
                puts("STORE ERR\n");
            }
        }else{
            puts("ERR\n");
            continue;
        }
    }
}