#include "MasterWriter.h"
#include "MasterReader.h"
#include "Omni.h"
#include "submaster.h"
#include "Controller.h"

int servo_power;

void cal_hana_catch() {
  servo_power = DS4.GetL2Toggle() ? 45 : 0;
//  if (LimitSw.GetBitData(1, 0) && LimitSw.GetBitData(1, 1) && LimitSw.GetBitData(1, 3)) {
//    omni.SetMaxPwm(0);
//    if (DS4.GetLeftxAxis() > 0)
//      omni.SetMaxPwm(15);
//  }
}
void send_hana() {
  for (int i = 1; i < 5; i++)
    servo.SetSingleData(i, servo_power);
}

void hana_show() {
  Serial.print(servo_power); Serial.print("\t");
}
