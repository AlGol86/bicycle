#include "iostm8s103f3.h"

#define rim() asm("rim")
#define sim() asm("sim")
#define nop() asm("nop")



#define PORT_iic_ODR       PC_ODR
#define PORT_iic_DDR       PC_DDR
#define PORT_iic_IDR       PC_IDR
#define PORT_iic_CR1       PC_CR1
#define PORT_iic_CR2       PC_CR2
#define pin_sda        6
#define bit_sda                           (1<<pin_sda)
#define pin_clk        5
#define bit_clk                           (1<<pin_clk)
#define WRITE 0
#define READ  1
#define ACK 1 //acknowledge
#define NOT_ACK 0 //not acknowledge

//iic
void sys_del_us(char del_us);
void sys_del_ms_iic(int del_ms);
char start_iic (char adr, char read_write_bit);
char send_byte (char data_byte);
unsigned char receive_byte (char acknowledge);
void stop_iic (void);

