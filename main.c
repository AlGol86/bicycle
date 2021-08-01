#include "led.h"
#include "iic.h"
#include "gy_521.h"
#include "main.h"
#include "scheduler.h"
#include "ADC_photo.h"

statement_t statement;
sys_time_t sys_time;
accel_buffer_t accel_buffer;

int main( void )
{
 sys_del_ms_iic(200);
 supply (on);
 initGY_521();
 
 int y=get_average_GY_521(AXEL_Y);  
 while(y==0){
    supply (off);
    sys_del_ms_iic(500);
    supply (on);
    sys_del_ms_iic(500);
    initGY_521();
    y=get_average_GY_521(AXEL_Y);  
 }

 
 out(init);
 init_tim2();
 blink(small_blinking);

 while(1){ // 52/255=0.2 sec/cycle  disp-off:35/255=0.13 sec/cycle

  statement.brightness=get_level_ADC(get_ADC(4)); //pin - D3:  AIN ch4
  
  if(putValueIntoBuffer(get_average_GY_521(AXEL_Z)/10, &accel_buffer))
    pulse_B5 (1000);
  
  if(check_condition_GY_521(270 + accel_buffer.zero_level, 20, -50 + accel_buffer.zero_level, accel_buffer, &statement.cond_f)) 
    stop_sign();
  
  if(may_sleep(&accel_buffer))
    sleep();
  
 }
}

