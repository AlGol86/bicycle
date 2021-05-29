#include "led.h"
#include "iic.h"
#include "gy_521.h"
#include "main.h"
#include "scheduler.h"

statement_t statement;
sys_time_t sys_time;


int main( void )
{
 sys_del_ms_iic(200);
 init_LED();
 supply (on);
 initGY_521();
 
 int y=get_average_GY_521(AXEL_Y);  
 while(y==0){
     printValue(8, 0); 
     supply (off);
     sys_del_ms_iic(500);
     supply (on);
     sys_del_ms_iic(500);
     initGY_521();
     y=get_average_GY_521(AXEL_Y);  
    }
 printValue(111, 0); 
 
 if(y<7000 && y>-7000) {
   statement.display=on;
 } else {
   statement.display=off; 
   sendCMD(CMD_DISP_OFF);
 }
 
 out(init);
 init_tim1();
 blink(ride);

 
 while(1){
  int val=0,yy=0,zz=0;
  val=get_average_GY_521(AXEL_X)/10;
  yy=get_average_GY_521(AXEL_Y)/10;
  zz=get_average_GY_521(AXEL_Z)/10;
  yy++;zz++;
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





