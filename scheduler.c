#include "scheduler.h"
#include "iostm8s103f3.h"
#include "main.h"

//add your scheduled tasks into task-enum 
//put your scheduled tasks into wwitch-cases:

void invoke_task(task_t task, int arg){
  switch(task){
    /*
     on_led,
  off_led,
  PWM_on_led,
  PWM_off_led,
  blink_bold,
  blink_small,
  stop_blinking,*/
    
  case on_led:
    out(on);
    break;
    
  case off_led:
    out(off);
    break;
    
  case PWM_on_led:
    PWM(arg);
    break;
    
  case PWM_off_led:
    PWM(arg);
    break;
    
  case blink_led:
    blink(arg);
    break;
  
    
  default:
    break;
  }
}

void init_tim1(void){
  TIM1_PSCRH=0;
  TIM1_PSCRL=1;
  TIM1_ARRH=1;
  TIM1_ARRL=100;
  TIM1_IER_UIE=1;
  asm("rim");
  TIM1_CR1_CEN=1;
}

void scedule(task_t task, int arg, int postponement, int period){
 extern sys_time_t sys_time;
 if(!sys_time.task_is_schedaled[task]) {
   sys_time.task_is_schedaled[task]=1;  
   if(sys_time.time==0){sys_time.time++;}
   if(postponement==0){postponement++;}
   sys_time.task_arg[task]=arg;
   sys_time.task_period[task]=period;
   sys_time.task_time[task]=sys_time.time+postponement;
 }
}

void cut_from_scedule(task_t task){
 extern sys_time_t sys_time;
 if(sys_time.task_is_schedaled[task]) {
   sys_time.task_is_schedaled[task]=0;
   sys_time.task_time[task]=0;
 }
}

__interrupt void tim1(void){
  extern sys_time_t sys_time;
  TIM1_SR1_UIF=0;
  if(sys_time.time==0){sys_time.time++;}
  char i_task;
  for(i_task=0;i_task<bottom_task;i_task++){
   if(sys_time.time==sys_time.task_time[i_task] ){
    invoke_task((task_t)i_task,sys_time.task_arg[i_task]);
    if(sys_time.task_period[i_task]!=0)
      sys_time.task_time[i_task]=sys_time.time+sys_time.task_period[i_task];
    else 
     sys_time.task_time[i_task]=0;
    
   }
  }
  sys_time.time++;
}