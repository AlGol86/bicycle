#include "led.h"
#include "main.h"
#include "scheduler.h"

void stop_light(){
blink(ride);
}

void blink(out_t blink){
  
extern statement_t statement;

  if(statement.blink!=blink){
    statement.blink=blink;
    switch(blink){
     case stop:
         cut_from_scedule(on_light);
         cut_from_scedule(off_light);
	 scedule(on_light, 0, 1, 7);
         scedule(off_light, 0, 5, 7);
         break;
    
     case ride:
         cut_from_scedule(on_light);
         cut_from_scedule(off_light);
	 scedule(on_light, 0, 1, 50);
         scedule(off_light, 0, 10, 50);
         break;
  
  
     case off:
        cut_from_scedule(on_light);
        cut_from_scedule(off_light);
        out(off);
        break;
    }
  }
}


void out(out_t out){
  switch(out){
  case init:{
	PORT_out_CR2&=~BIT_out;
	PORT_out_CR1&=~BIT_out;
	PORT_out_ODR|=BIT_out;
	PORT_out_DDR|=BIT_out;
	sysDelay(200);
        break;
  }
  case on:{
  PORT_out_ODR&=~BIT_out;
  break;
  }
  case off:{
  PORT_out_ODR|=BIT_out;
  break;
  }
 }
}
  
