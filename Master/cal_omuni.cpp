#include<arduino.h>
#include"PidController.h"
#include"enc_board_mbed.h"

PidController pid_omuni1 (7, 0, 0.2, 10000, 300.0);
PidController pid_omuni2 (7, 0, 0.2, 10000, 300.0);
PidController pid_omuni3 (7, 0, 0.2, 10000, 300.0);
PidController pid_omuni4 (7, 0, 0.2, 10000, 300.0);
EncoderBoardMbed enc_omuni1(11);
EncoderBoardMbed enc_omuni2(12);
EncoderBoardMbed enc_omuni3(13);
EncoderBoardMbed enc_omuni4(14);

int MaxPower = 80;
int Motor_power_omuni1;
int Motor_power_omuni2;
int Motor_power_omuni3;
int Motor_power_omuni4;
byte Motor_power_omuni_muki;
byte Motor_power1_Send;
byte Motor_power2_Send;
byte Motor_power3_Send;
byte Motor_power4_Send;
byte Motor_muki_Send;

void  cal_omuni(byte move_X, byte move_Y, byte move_turn, int turn_Gyro) {
  pinMode(4, INPUT_PULLUP);
  enc_omuni1.Update();
  enc_omuni2.Update();
  enc_omuni3.Update();
  enc_omuni4.Update();
  int cal_X, cal_Y, cal_turn;

  cal_X = map(move_X, 0, 255, -255, 255);
  cal_Y = map(move_Y, 0, 255, -255, 255);
  cal_turn = map(move_turn, 0, 255, -255, 255);

  if (abs(cal_X) < 30) {
    cal_X = 0;
  }
  if (abs(cal_Y) < 30) {
    cal_Y = 0;
  }
  if (abs(cal_turn) < 30) {
    cal_turn = 0;
  }

  Motor_power_omuni1 = -cal_X + cal_Y + cal_turn + turn_Gyro;
  Motor_power_omuni2 = -cal_X - cal_Y + cal_turn + turn_Gyro;
  Motor_power_omuni3 = cal_X - cal_Y + cal_turn + turn_Gyro;
  Motor_power_omuni4 = cal_X + cal_Y + cal_turn + turn_Gyro;

  pid_omuni1.Update(PI * 29 * enc1.getCount(2) / 4096, PI * 29 * enc1.getCount(2) / 4096 + Motor_power_omuni1);
  pid_omuni2.Update(PI * 29 * enc1.getCount(2) / 4096, PI * 29 * enc1.getCount(2) / 4096 + Motor_power_omuni2);
  pid_omuni3.Update(PI * 29 * enc1.getCount(2) / 4096, PI * 29 * enc1.getCount(2) / 4096 + Motor_power_omuni3);
  pid_omuni4.Update(PI * 29 * enc1.getCount(2) / 4096, PI * 29 * enc1.getCount(2) / 4096 + Motor_power_omuni4);

  Motor_power_omuni1=pid_omuni1.GetPower();
  Motor_power_omuni2=pid_omuni2.GetPower();
  Motor_power_omuni3=pid_omuni3.GetPower();
  Motor_power_omuni4=pid_omuni4.GetPower();
  
  int Max_power = max(max(abs(Motor_power_omuni1), abs( Motor_power_omuni2)), max(abs(Motor_power_omuni3), abs(Motor_power_omuni4)));
  if (Max_power > MaxPower) {
    float amp = float(MaxPower) / Max_power;
    Motor_power_omuni1 = Motor_power_omuni1 * amp;
    Motor_power_omuni2 = Motor_power_omuni2 * amp;
    Motor_power_omuni3 = Motor_power_omuni3 * amp;
    Motor_power_omuni4 = Motor_power_omuni4 * amp;
  }
  if (Motor_power_omuni1 > 0) {
    Motor_power1_Send = Motor_power_omuni1;
    bitWrite(Motor_muki_Send, 0, 0);
  } else {
    Motor_power1_Send = abs(Motor_power_omuni1);
    bitWrite(Motor_muki_Send, 0, 1);
  }
  if (Motor_power_omuni2 > 0) {
    Motor_power2_Send = Motor_power_omuni2;
    bitWrite(Motor_muki_Send, 1, 0);
  } else {
    Motor_power2_Send = abs(Motor_power_omuni2);
    bitWrite(Motor_muki_Send, 1, 1);
  }
  if (Motor_power_omuni3 > 0) {
    Motor_power3_Send = Motor_power_omuni3;
    bitWrite(Motor_muki_Send, 2, 0);
  } else {
    Motor_power3_Send = abs(Motor_power_omuni3);
    bitWrite(Motor_muki_Send, 2, 1);
  }
  if (Motor_power_omuni4 > 0) {
    Motor_power4_Send = Motor_power_omuni4;
    bitWrite(Motor_muki_Send, 3, 0);
  } else {
    Motor_power4_Send = abs(Motor_power_omuni4);
    bitWrite(Motor_muki_Send, 3, 1);
  }
}

byte Motor_power_omuni_1() {
  return Motor_power1_Send;
}
byte Motor_power_omuni_2() {
  return Motor_power2_Send;
}
byte Motor_power_omuni_3() {
  return Motor_power3_Send;
}
byte Motor_power_omuni_4() {
  return Motor_power4_Send;
}
byte Motor_power_omuni_Send_muki() {
  return Motor_muki_Send;
}
