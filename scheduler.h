#include "iostm8s103f3.h"

#pragma vector=13
__interrupt void tim1(void);
void init_tim1(void);

//put tasks here
typedef enum {
  on_led,
  off_led,
  PWM_on_led,
  PWM_off_led,
  blink_led,
  bottom_task} task_t;

typedef struct{
int time;
int task_time[bottom_task];
int task_arg[bottom_task];
int task_period[bottom_task];
int task_is_schedaled[bottom_task];
} sys_time_t;

void scedule(task_t task, int arg, int postponement, int period);
void cut_from_scedule(task_t task);
void invoke_task(task_t task, int arg);
