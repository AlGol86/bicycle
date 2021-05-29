#include "iostm8s103f3.h"
#define PORT_out_ODR       PA_ODR
#define PORT_out_DDR       PA_DDR
#define PORT_out_IDR       PA_IDR
#define PORT_out_CR1       PA_CR1
#define PORT_out_CR2       PA_CR2
#define PIN_out   3
#define BIT_out  (1<<PIN_out)

#define PORT_supply_ODR       PC_ODR
#define PORT_supply_DDR       PC_DDR
#define PORT_supply_IDR       PC_IDR
#define PORT_supply_CR1       PC_CR1
#define PORT_supply_CR2       PC_CR2
#define pin_plus         3
#define bit_plus                           (1<<pin_plus)
#define pin_minus        4
#define bit_minus                          (1<<pin_minus)
#define bit_mask_plus_minus  (bit_plus | bit_minus)

#ifndef MAIN_H
#define MAIN_H

typedef enum{off,init,on,half_on,half_off,ride,stop} out_t;


typedef struct{
  out_t blink;
  char cond_f;
  out_t display;
} statement_t;

void out(out_t out);
void blink(out_t blink);
void stop_light(void);
void supply (out_t mode);
#endif
