#include<arduino.h>
#include"PidController.h"
#include"enc_board_mbed.h"

PidController pid_shoukou (7, 0, 0.2, 10000, 300.0);
EncoderBoardMbed enc1(10);
byte Motor_power_shoukou_send;
byte Motor_muki_shoukou_send;

int Motor_power_shoukou_cal;
int set;

void cal_syoukou(byte move_Motor) {
  pinMode(3,INPUT_PULLUP);
  enc1.Update();
  if (set == 0) {
   Motor_power_shoukou_send = 25;
      Motor_muki_shoukou_send = 1;
      if(digitalRead(3)==LOW){
        set=1;
        }
  } else {
    if (move_Motor == 0) {
      pid_shoukou.Update(PI * 29 * enc1.getCount(2) / 4096, 0);
    } else {
      pid_shoukou.Update(PI * 29 * enc1.getCount(2) / 4096, 100);
    }

    Motor_power_shoukou_cal = constrain(pid_shoukou.GetPower(), -80, 80);
    if (Motor_power_shoukou_cal < 0) {
      Motor_power_shoukou_send = abs(Motor_power_shoukou_cal);
      Motor_muki_shoukou_send = 1;
    } else {
      Motor_power_shoukou_send = abs(Motor_power_shoukou_cal);
      Motor_muki_shoukou_send = 0;
    }
  }
}
byte Motor_power_shoukou() {
  return Motor_power_shoukou_send;
}
byte Motor_muki_shoukou() {
  return Motor_muki_shoukou_send;
}
