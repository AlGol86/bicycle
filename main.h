#include "iostm8s103f3.h"
#define PORT_out_ODR       PA_ODR
#define PORT_out_DDR       PA_DDR
#define PORT_out_IDR       PA_IDR
#define PORT_out_CR1       PA_CR1
#define PORT_out_CR2       PA_CR2
#define PIN_out   3
#define BIT_out  (1<<PIN_out)

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
#endif
