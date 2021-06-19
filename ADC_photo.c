#include "iostm8s103f3.h"

char get_level_ADC(int value){
char x;
if(value > 800)         x=0;	//dark
else if(value > 500) 	x=1;
else if(value > 350)    x=2;
else if(value > 250)    x=3;
else                    x=4;   //bright
return x;
}

unsigned int get_ADC(char ch)
{
char h=0;
char l=0;
  ADC_CSR_CH=ch;
  ADC_CR1_ADON=1; 
  ADC_CR1_ADON=1;  //dubble 'ADON" for switch on ADC
while((ADC_CSR_EOC)==0)
  {}

ADC_CSR_EOC=0;
h=ADC_DRH;
l=ADC_DRL;
return ((h<<2)|l); 
}
