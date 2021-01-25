
#include "im920_v2.h"
#include "LoopCycleController.h"
#include "MasterWriter.h"
#include "PidController.h"
#include "enc_board_mbed.h"

LoopCycleController loopCtrl(10000);
MasterWriter motor1(3, 5);
PidController first (7, 0, 0.2, loopCtrl.Cycle_us(), 300.0);
EncoderBoardMbed enc1(10);
IM920 im920(800);

bool set = 1;

void setup() {
  Wire.begin();
  Wire.setClock(400000UL);
  Serial.begin(115200);
  enc1.init();
  pinMode(3, INPUT_PULLUP);
}

void loop() {
  im920.Update();
  enc1.Update();

  if (set) {
    motor1.SetMotorData(2, -25);
    if (!digitalRead(3)) {
      enc1.resetCount(2);
      set = 0;
    }
  }
  else {
    first.Update(PI * 29 * enc1.getCount(2) / 4096, im920.GetGreenSwitchToggle() ? 100 : 0);
    motor1.SetMotorData(2, constrain(first.GetPower(), -50, 50));
  }



  if (im920.GetRedSwitch())
    motor1.reset();

  motor1.Update();

  Serial.print(enc1.getCount(2)); Serial.print("\t");
  Serial.print(first.GetPower()); Serial.print("\t");
  Serial.print(digitalRead(3)); Serial.print("\t");
  Serial.println(PI * 29 * enc1.getCount(2) / 4096);

  loopCtrl.Update();
}
