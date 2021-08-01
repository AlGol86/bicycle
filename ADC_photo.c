#include "iostm8s103f3.h"
/* AIN CH3 - D2
*  AIN CH4 - D3
*  AIN CH5 - D5
*  AIN CH6 - D6
*/

char get_level_ADC(int value){
char x;
if(value > 800)         x=0;	//dark
else if(value > 650) 	x=1;
else if(value > 550)    x=2;
else if(value > 450)    x=3;
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
