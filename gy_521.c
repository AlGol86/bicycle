#include "iostm8s103f3.h"
#include "gy_521.h"
#include "iic.h"
#include "main.h"

void setRegAddrGY_521(char reg_addr){
  start_iic(GY_521_addr,WRITE);
  send_byte (reg_addr);
  stop_iic();
}

void setValueGY_521(char reg_addr,char value){
	start_iic(GY_521_addr,WRITE);
  send_byte (reg_addr);
  send_byte (value);
  stop_iic();
}

char getValueGY_521(char reg_addr){
	setRegAddrGY_521(reg_addr);
  return getByteGY_521();
}

char getByteGY_521(){
	char data_byte;
  start_iic(GY_521_addr,READ);
  data_byte=receive_byte(NOT_ACK);
  stop_iic();
  return data_byte;
}

void getBurstGY_521(char* data, char n){
	char i;
  start_iic(GY_521_addr,READ);
	for(i=0;i<n-1;i++){
  *(data+i)=receive_byte(ACK);
  }
  *(data+(n-1))=receive_byte(NOT_ACK);
  stop_iic();
  
}

void initGY_521(accel_buffer_t* accel_buffer){
        sys_del_ms_iic(100);
	getValueGY_521(MPU6050_PWR_MGMT_1);
	setValueGY_521(MPU6050_PWR_MGMT_1,0);
        sys_del_ms_iic(100);
        accel_buffer->zero_level = get_average_GY_521(AXEL_Z)/10;
}

int get_TXYZ_GY_521(char data_type){
	char array[2];
	int XYZT;
	setRegAddrGY_521(MPU6050_ACCEL_XOUT_H+data_type);
	getBurstGY_521(array, 2);
	XYZT=(array[0]<<8)+array[1];
	if (data_type == TEMP)	{XYZT/=34;return XYZT+365;}
	else {
         // if(XYZT<-15000) XYZT=-15000;
          return XYZT;
        }
}

int get_average_GY_521(char data_type){
 int i,j;
 int x[]={0,0,0};
 
 for(j=0;j<3;j++){
  for(i=0;i<20;i++){
   x[j]+=get_TXYZ_GY_521(data_type)/10;
  } 
  x[j]/=2;
 }
 return get_mediana(&x[0]);
}

char putValueIntoBuffer(int value, accel_buffer_t* accel_buffer) {
  char zero_set=0;
  accel_buffer->current_val = value;
  
  if(!(accel_buffer->counter & 0x01)) //0.3 s - fast
    accel_buffer->fast_buffer[(accel_buffer->counter & 0x06) >>1] = value;
  
  if(!(accel_buffer->counter & 0x3F)) { //10s - middle
    accel_buffer->middle_buffer[(accel_buffer->counter & 0xc0) >> 6] = value;  
  }
  
  if(!(accel_buffer->counter)) { //37 s
    accel_buffer->slow_buffer[accel_buffer->slow_counter& 0x07] =  value; 
    zero_set = autoset_zerolevel(accel_buffer); 
    accel_buffer->slow_counter ++;
  }
  
  accel_buffer->counter++;
  return zero_set;
}

char autoset_zerolevel(accel_buffer_t* accel_buffer){
  int a = accel_buffer->middle_buffer[0];
  int b = accel_buffer->middle_buffer[1];
  int c = accel_buffer->middle_buffer[2];
  int d = accel_buffer->middle_buffer[3];
  int dx = 10;
  if(equals(a, b, dx) && equals(b, c, dx) && equals(c, d, dx) && equals(a, d, dx)){
    accel_buffer->zero_level = ((a+b+c+d)/4);
    return 1;
  } else {
    return 0;
  }
}

char may_sleep(accel_buffer_t* accel_buffer){
  int a = accel_buffer->middle_buffer[0];
  int b = accel_buffer->middle_buffer[1];
  int c = accel_buffer->middle_buffer[2];
  int d = accel_buffer->middle_buffer[3];
  int dx1 = 3;
  int dx2 = 10;
  if(equals(a, b, dx1) && equals(b, c, dx1) && equals(c, d, dx1) && equals(a, d, dx1)){
    accel_buffer->sleep = 1;
  } else if (!equals(a, b, dx2) || !equals(b, c, dx2) || !equals(c, d, dx2) || !equals(a, d, dx2)){
    accel_buffer->sleep = 0;
  }
  return accel_buffer->sleep;
}

char may_halt(accel_buffer_t* accel_buffer){
  int dx = 3;
  if(equals(accel_buffer->slow_buffer[0], accel_buffer->slow_buffer[1], dx) && equals(accel_buffer->slow_buffer[1], accel_buffer->slow_buffer[2], dx) \
    && equals(accel_buffer->slow_buffer[2], accel_buffer->slow_buffer[3], dx) && equals(accel_buffer->slow_buffer[3], accel_buffer->slow_buffer[4], dx)\
     && equals(accel_buffer->slow_buffer[4], accel_buffer->slow_buffer[5], dx) && equals(accel_buffer->slow_buffer[5], accel_buffer->slow_buffer[6], dx) \
      && equals(accel_buffer->slow_buffer[6], accel_buffer->slow_buffer[7], dx) && accel_buffer->slow_buffer[7] != 0){
    accel_buffer->halt = 1;
    }
  return accel_buffer->halt;
}

int get_mediana(int* data){
 int res;
 int x[3];
 x[0]=*data;
 x[1]=*(data+1);
 x[2]=*(data+2);
  
 if(x[0]<x[1] && x[0]<x[2] ) res=(x[1]<x[2])?x[1]:x[2];
 else if(x[1]<x[0] && x[1]<x[2] )res=(x[0]<x[2])?x[0]:x[2];
 else res=(x[0]<x[1])?x[0]:x[1];
 
 return res;
}

char check_condition_GY_521(int threshold, char hyst, int min_threshold, accel_buffer_t accel_buffer, char* cond_f){
  	
  if((accel_buffer.current_val > (threshold+hyst)) \
    & (accel_buffer.fast_buffer[0] > min_threshold) \
      & (accel_buffer.fast_buffer[1] > min_threshold) \
        & (accel_buffer.fast_buffer[2] > min_threshold) \
          & (accel_buffer.fast_buffer[3] > min_threshold)) 
  {*cond_f=1;return 1;}
  else if(accel_buffer.current_val < threshold) 
  {*cond_f=0;return 0;}
  else if (*cond_f) 
    return 1;
  else 
    return 0;
}

char equals(int a, int b, int dx) {
  if(((a >= b) & (a<=(b+dx))) || ((a <= b) & (a>=(b-dx)))) 
    return 1;
  else 
    return 0;
}