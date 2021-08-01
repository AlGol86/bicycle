#include "iostm8s103f3.h"
#define PORT_out_ODR       PD_ODR
#define PORT_out_DDR       PD_DDR
#define PORT_out_IDR       PD_IDR
#define PORT_out_CR1       PD_CR1
#define PORT_out_CR2       PD_CR2
#define PIN_out   4
#define BIT_out  (1<<PIN_out)

#define PORT_supply_ODR       PC_ODR
#define PORT_supply_DDR       PC_DDR
#define PORT_supply_IDR       PC_IDR
#define PORT_supply_CR1       PC_CR1
#define PORT_supply_CR2       PC_CR2
#define pin_minus        7
#define bit_minus                          (1<<pin_minus)

#ifndef MAIN_H
#define MAIN_H

typedef enum{off, init, on, small_blinking, bold_blinking, sleep_blinking, small, bold } out_t;

typedef struct{
  out_t blink;
  char cond_f;
  out_t display;
  char brightness;
} statement_t;


void stop_sign(void);
void sleep(void);
void blink(out_t blink);
void PWM(out_t out);
void out(out_t out);
void supply (out_t mode);
void pulse_B5 (int duration);
void B5_off(); 
#endif