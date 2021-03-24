#include "Controller.h"
#include "MasterWriter.h"
#include "MasterReader.h"
#include "submaster.h"
#include "Gyro.h"
#include "PidController.h"
#include "enc_board_teensy.h"
#include "Omni.h"

double shouko_power;
long time_set;
bool flag = true;
bool flag2;

void cal_shouko() {
  if (flag2) {
    shouko_power = DS4.GetTriangle() && (PI * 29 * enc1.getCount(1) / 8192) < 715  ? -200 : DS4.GetDown() && !LimitSw.GetBitData(1, 7) ? 200 : 0;

    if (DS4.GetTriangle() && DS4.GetSelect()) {
      shouko_power = -100;
    }
  }
}

void stop_shouko() {
  if (DS4.GetCrossToggle())
    shouko_power = 0;
}

void send_shouko() {
  motor2.SetMotorData(1, shouko_power);
}

void set_shouko() {
  if (flag) {
    time_set = millis();
    flag = false;
  }
  shouko_power = -50;
  if (millis() - time_set > 3000) {
    shouko_power = 50;
    if (LimitSw.GetBitData(1, 7)) {
      shouko_power = 0;
      enc1.resetCount(1);
      flag2 = true;
    }
  }
}

void show_shouko() {
  //  Serial.print(millis() - time_set); Serial.print("\t");
  Serial.print(PI * 29 * enc1.getCount(1) / 8192); Serial.print("\t");
  //  Serial.print(shouko_power); Serial.print("\t");
}
