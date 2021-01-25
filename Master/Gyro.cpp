#include<arduino.h>
#include"Gyro.h"
#include"pidController.h"

PidController test(3, 0, 0.2, 10000, 300);
Gyro gyro;

int getpower;
int turning1;
int timer_count;
byte flag;

void Gyro_cal(byte turning, byte stop_Gyro, byte Gyro_reset) {
  turning1 = map(turning, 0, 255, -255, 255);
  if (abs(turning1) < 30) {
    turning = 0;
  } else {
    turning = 1;
  }
  gyro.GetGyro();
  gyro.GyroCaluculate();
  getpower = test.GetPower();
  if (stop_Gyro == 0) {
    timer_count = 200;
    if (timer_count > 0) {
      gyro.OffSet_Update();
      timer_count--;
    }
  } else if (Gyro_reset == 1) {
    gyro.OffSet_Update();
  } else if (turning1 == 0) {
    if (flag) {
      gyro.OffSet_Update();
      static int i;
      i++;
      if (i < 100)
        flag = false;
      else if (i >= 100) {
        i = 0;
        flag = true;
      }
    }
    else {
      test.Update(gyro.yaw(), 0);
    }
  }
  else if (abs(turning1) > 0) {
    flag = true;
  }
}

int Gyro_power() {
  return getpower;
}
