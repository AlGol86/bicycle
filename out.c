#include "main.h"
#include "scheduler.h"
#include "iic.h"

void stop_sign(){
blink(bold_blinking);
cut_from_scedule(blink_led);
scedule(blink_led,small_blinking, 4000, 0);//2000
}

void sleep(){
blink(sleep_blinking);
cut_from_scedule(blink_led);
scedule(blink_led,small_blinking, 1000, 0);
}

void alarm(int level){
  extern statement_t statement;
  if(level<0) level=-level;
  if(statement.alarm_on!=1 && statement.blink==off){
     statement.alarm_on=1; 
     cut_from_scedule(blink_led);
     scedule(blink_led,alarm_blinking, 1000, 0);
  }
  
  if(statement.blink==alarm_blinking && statement.alarm_on==1){
     statement.alarm_on=0; 
     cut_from_scedule(blink_led);
     scedule(blink_led,off, level, 0);
  }
}

void blink(out_t blink){
  
extern statement_t statement;

  if(statement.blink!=blink){
    statement.blink=blink;
    switch(blink){
     case small_blinking:
         cut_from_scedule(PWM_on_led);
         cut_from_scedule(PWM_off_led);
         scedule(PWM_on_led, small, 1, 1000);
         scedule(PWM_off_led, off, 120, 1000);//60 500
         break;
    
     case bold_blinking:
         cut_from_scedule(PWM_on_led);
         cut_from_scedule(PWM_off_led);
         scedule(PWM_on_led, bold, 1, 200);// 1 100
         scedule(PWM_off_led, off, 50, 200);//25 100
         break;
         
     case sleep_blinking:
         cut_from_scedule(PWM_on_led);
         cut_from_scedule(PWM_off_led);
         scedule(PWM_on_led, small, 1, 10000);// 1 100
         scedule(PWM_off_led, off, 20, 10000);//25 100
         break;
         
     case alarm_blinking:
         cut_from_scedule(PWM_on_led);
         cut_from_scedule(PWM_off_led);
         scedule(PWM_on_led, small, 1, 100);
         scedule(PWM_off_led, off, 10, 100);
         break;
     
     case off:
        cut_from_scedule(PWM_on_led);
        cut_from_scedule(PWM_off_led);
        PWM(off);
        break;
    }
  }
}


void PWM(out_t out_v){
  extern statement_t statement;
  char period=30;
  char brightness_val_1[5]={2,2,3,5,10};
  char brightness_val_2[5]={3,5,8,15,30};
  switch(out_v){
  
      case small:
         cut_from_scedule(on_led);
         cut_from_scedule(off_led);
         scedule(on_led,  0, 1, period);
         scedule(off_led, 0, brightness_val_1[statement.brightness], period);
         break;
         
      case bold:
         cut_from_scedule(on_led);
         cut_from_scedule(off_led);
         scedule(on_led,  0, 1, period);
         scedule(off_led, 0, brightness_val_2[statement.brightness] , period);
         break;
         
      case off:
         cut_from_scedule(on_led);
         cut_from_scedule(off_led);
         out(off);
         break;
         
      default:
         break;
  }
}

void out(out_t out){
  
  switch(out){
   
    case init:
	 PORT_out_CR2&=~BIT_out;
	 PORT_out_CR1|=BIT_out;
	 PORT_out_ODR&=~BIT_out;
	 PORT_out_DDR|=BIT_out;
	 break;
  
    case on:
        PORT_out_ODR|=BIT_out;
        break;
  
    case off:
        PORT_out_ODR&=~BIT_out;
        break;
               
    default:
        break;
  }
}

  void supply (out_t mode)
{	
   switch(mode){
 
    case on:
        PORT_supply_CR2|=bit_minus;
	PORT_supply_CR1&=~bit_minus;
	PORT_supply_ODR&=~bit_minus; 
	PORT_supply_DDR|=bit_minus;;
        break;
  
    case off:
        PORT_supply_ODR|=bit_minus;
        break;
        
    case reset:
        supply (off);
        sys_del_ms_iic(500);
        supply (on);
        sys_del_ms_iic(500);
        break;
               
    default:
        break;
  }
}

void pulse_B5 (int duration){
  PB_DDR|=0x20;
  scedule(b5_off,  0, duration, 0);
}

void B5_off() {
  PB_DDR&=~0x20;
}
       