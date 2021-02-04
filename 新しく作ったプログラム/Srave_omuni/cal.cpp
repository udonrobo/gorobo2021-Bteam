#include<arduino.h>

int Motor_power1_Send;
int Motor_power2_Send;
int Motor_power3_Send;
int Motor_power4_Send;

int Motor_power1_cal;
int Motor_power2_cal;
int Motor_power3_cal;
int Motor_power4_cal;

int Motor_muki1_cal;
int Motor_muki2_cal;
int Motor_muki3_cal;
int Motor_muki4_cal;


void cal(byte Motor_power1, byte Motor_power2, byte Motor_power3, byte Motor_power4, byte Motor_muki) {
  Motor_muki1_cal = bitRead(Motor_muki, 0);
  Motor_muki2_cal = bitRead(Motor_muki, 1);
  Motor_muki3_cal = bitRead(Motor_muki, 2);
  Motor_muki4_cal = bitRead(Motor_muki, 3);

  if (Motor_muki1_cal == 0) {
    Motor_power1_Send = Motor_power1;
  } else {
    Motor_power1_Send = Motor_power1 * -1;
  }

 if (Motor_muki2_cal == 0) {
    Motor_power2_Send = Motor_power2;
  } else {
    Motor_power2_Send = Motor_power2 * -1;
  }

   if (Motor_muki3_cal == 0) {
    Motor_power3_Send = Motor_power3;
  } else {
    Motor_power3_Send = Motor_power3 * -1;
  }

   if (Motor_muki4_cal == 0) {
    Motor_power4_Send = Motor_power4;
  } else {
    Motor_power4_Send = Motor_power4 * -1;
  }
}

int Motor_power1_back(){
  return Motor_power1_Send;
  }
int Motor_power2_back(){
  return Motor_power2_Send;
  }
int Motor_power3_back(){
  return Motor_power3_Send;
  }
int Motor_power4_back(){
  return Motor_power4_Send;
  }
  
