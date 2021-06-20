#include "main.h"
#include "scheduler.h"

void stop_sign(){
blink(bold_blinking);
cut_from_scedule(blink_led);
scedule(blink_led,small_blinking, 4000, 0);
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
         scedule(PWM_off_led, off, 120, 1000);
         break;
    
     case bold_blinking:
         cut_from_scedule(PWM_on_led);
         cut_from_scedule(PWM_off_led);
         scedule(PWM_on_led, bold, 1, 200);
         scedule(PWM_off_led, off, 50, 200);
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
  char brightness_val_1[5]={2,2,3,4,5};
  char brightness_val_2[5]={3,4,7,15,30};
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
         scedule(on_led,  0, 1,period);
         scedule(off_led, 0, brightness_val_2[statement.brightness], period);
         break;
         
      case off:
         cut_from_scedule(on_led);
         cut_from_scedule(off_led);
         out(off);
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
  }
}

  void supply (out_t mode)
{	
        
        if(mode==on){
        PORT_supply_CR2&=~bit_mask_plus_minus; 
	PORT_supply_CR1|=bit_mask_plus_minus; 
	PORT_supply_ODR|=bit_plus; 
        PORT_supply_ODR&=~bit_minus; 
	PORT_supply_DDR|=bit_mask_plus_minus; 
        } else{PORT_supply_ODR&=~bit_plus; }
       
								
}
