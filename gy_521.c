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

void initGY_521(){
        sys_del_ms_iic(200);
	getValueGY_521(MPU6050_PWR_MGMT_1);
	setValueGY_521(MPU6050_PWR_MGMT_1,0);
        sys_del_ms_iic(100);
}

int get_TXYZ_GY_521(char data_type){
	char array[2];
	int XYZT;
	setRegAddrGY_521(MPU6050_ACCEL_XOUT_H+data_type);
	getBurstGY_521(array, 2);
	XYZT=(array[0]<<8)+array[1];
	if (data_type == TEMP)	{XYZT/=34;return XYZT+365;}
	else return XYZT;
}

int get_average_GY_521(char data_type){
 int i;
 int x=0;
 for(i=0;i<20;i++){
 x+=get_TXYZ_GY_521(data_type)/10;
 }
 x/=2;
 return x;


}

char check_condition_GY_521(int threshold, int hyst, int val){
  extern statement_t statement;
  	
  if     (val > (threshold+hyst)) {statement.cond_f=1;return 1;}
  else if(val < threshold) {statement.cond_f=0;return 0;}
  else if (statement.cond_f) return 1;
  else return 0;
}