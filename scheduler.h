#include "iostm8s103f3.h"

#pragma vector=15
__interrupt void tim2(void);
void init_tim2(void);
void init_tim1(void);
//put tasks here
typedef enum {
  on_led,
  off_led,
  PWM_on_led,
  PWM_off_led,
  blink_led,
  b5_off,
  bottom_task} task_t;

typedef struct{
unsigned int time;
unsigned int task_time[bottom_task];
int task_arg[bottom_task];
unsigned int task_period[bottom_task];
char task_is_schedaled[bottom_task];
} sys_time_t;

void scedule(task_t task, int arg, int postponement, unsigned int period);
void cut_from_scedule(task_t task);
void invoke_task(task_t task, int arg);
