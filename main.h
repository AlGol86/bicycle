#include "iostm8s103f3.h"
#define PORT_out_ODR       PB_ODR
#define PORT_out_DDR       PB_DDR
#define PORT_out_IDR       PB_IDR
#define PORT_out_CR1       PB_CR1
#define PORT_out_CR2       PB_CR2
#define PIN_out   4
#define BIT_out  (1<<PIN_out)

#ifndef MAIN_H
#define MAIN_H

typedef enum{init,on,off,ride,stop} out_t;


typedef struct{
  out_t blink;
  char cond_f;
} statement_t;

void out(out_t out);
void blink(out_t blink);
void stop_light(void);
#endif