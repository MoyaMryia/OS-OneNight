#ifndef UART
#define UART

#define UART0 0x10000000

#define UART_RHR 0
#define UART_THR 0
#define UART_LSR 5

#define LSR_RX_READY (1 << 0)
#define LSR_TX_IDLE  (1 << 5)

#define UART_REG(reg) ((volatile char *)(UART0 + reg))

int sendSingleChar(char ch);
void sendChar(char ch);
void putchar(char ch);
void sendText_f(char *str, unsigned int str_len);
void sendText(char *str);
void puts(char *str);

int getSingleChar();
char getChar();
int getLine(char *buf, int maxlen);
#endif