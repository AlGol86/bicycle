#include "iostm8s103f3.h"

#pragma vector=13
__interrupt void tim1(void);
void init_tim1(void);


typedef enum {
  on_light,
  off_light,
  stop_off_task,
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
