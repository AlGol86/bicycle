#include "led.h"
#include "iic.h"
#include "gy_521.h"
#include "main.h"
#include "scheduler.h"
#include "ADC_photo.h"

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
 blink(small_blinking);
  
 while(1){

  statement.brightness=get_level_ADC(get_ADC(4));
  int val=0;
  val=get_average_GY_521(AXEL_X)/10;
  if(statement.display){
  printValue(val, 0); 
  }
  if(check_condition_GY_521(300,20,val)) {  
   stop_sign();
  }
 }
}

