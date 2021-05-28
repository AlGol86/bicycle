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
 initGY_521();
 init_LED();
 out(init);
 init_tim1();
 blink(ride);
 int y=get_average_GY_521(AXEL_Y);
 if(y<7000 && y>-7000) {
   statement.display=on;
 } else {
   statement.display=off; 
   sendCMD(CMD_DISP_OFF);
 }
 
 while(1){
  int val=0;
  val=get_average_GY_521(AXEL_X)/10;
  if(statement.display){
  printValue(val, 0); 
  }
  if(check_condition_GY_521(300,20,val)) {  
   blink(stop);
   cut_from_scedule(stop_off_task);
   scedule(stop_off_task,0,5000,0);
  }
 }
}







