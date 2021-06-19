#include "iostm8s103f3.h"

#define PIN_ADC_chanal_3     2  //port D(ch#3)
#define BIT_ADC_chanal_3    (1<<PIN_ADC_chanal_3 )
#define PIN_ADC_chanal_4     3  //port D(ch#4)
#define BIT_ADC_chanal_4    (1<<PIN_ADC_chanal_4 )
#define PIN_ADC_chanal_5     5  //port D(ch#5)
#define BIT_ADC_chanal_5    (1<<PIN_ADC_chanal_5 )
#define PIN_ADC_chanal_6     6  //port D(ch#6)
#define BIT_ADC_chanal_6    (1<<PIN_ADC_chanal_6 )
#define BIT_MASK_ch3456      (BIT_ADC_chanal_3|BIT_ADC_chanal_4|BIT_ADC_chanal_5|BIT_ADC_chanal_6)

unsigned int get_ADC(char ch);
char get_level_ADC(unsigned int value);