#include<arduino.h>
#include"MovingAverage.h"
MovingAverage average(100);
int Motor_Speed;

void cal(byte Motor_power_cal, byte Motor_muki_cal) {
  if (Motor_muki_cal == 0) {
    Motor_Speed = Motor_power_cal;
  } else {
    Motor_Speed = Motor_power_cal * -1;
  }
}

int Motor_power_Send() {
  return Motor_Speed;
}
