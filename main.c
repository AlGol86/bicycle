#include "led.h"
#include "iic.h"
#include "gy_521.h"
#include "main.h"
#include "scheduler.h"

statement_t statement;
sys_time_t sys_time;


int main( void )
{
 supply ();
 initGY_521();
 init_LED();
 out(init);
 init_tim1();
 blink(ride);
 while(1){
  int x=get_average_GY_521(AXEL_X)/10;
  printValue((int long)x, 0); 
 
  if(check_condition_GY_521(500,100,x)) {  
   blink(stop);
   cut_from_scedule(stop_off_task);
   scedule(stop_off_task,0,300,0);
  }
 }
}



