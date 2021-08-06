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
 initGY_521(&accel_buffer);
 while(!get_average_GY_521(AXEL_Y)){
    supply (reset);
    initGY_521(&accel_buffer);
 }
 
 out(init);
 init_tim2();
 
 int adjusting_error = get_average_GY_521(AXEL_Z)/10;
 while(!equals(0,adjusting_error,100)){
   alarm(adjusting_error);
   adjusting_error = get_average_GY_521(AXEL_Z)/10;
 }
 
 cut_from_scedule(blink_led);
 sys_del_ms_iic(2000);
 initGY_521(&accel_buffer);
 
 
 blink(small_blinking);

 while(1){ // 52/255=0.2 sec/cycle  disp-off:35/255=0.13 sec/cycle 

  statement.brightness=get_level_ADC(get_ADC(4)); //pin - D3:  AIN ch4 //<0.005s
  
  if(putValueIntoBuffer(get_average_GY_521(AXEL_Z)/10, &accel_buffer)) //0.16s
    pulse_B5 (1000);
  
  if(check_condition_GY_521(260 + accel_buffer.zero_level, 20, -100 + accel_buffer.zero_level, accel_buffer, &statement.cond_f)) //<0.01 s
    stop_sign(); 
  
  if(may_sleep(&accel_buffer))
    sleep();
  
  if(may_halt(&accel_buffer))
    halt();
 }
}

