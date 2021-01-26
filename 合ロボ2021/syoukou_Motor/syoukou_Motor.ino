#include<Wire.h>
#include"LoopCyclecontroller.h"
#include"subMaster.h"

LoopCycleController loopCtrl(1000);

byte Motor_power;
byte Motor_muki;

const int Motor_pin_a = 8;
const int Motor_pin_b = 10;
const int Motor_pin_p = 9;

int Motor_OUTPUT;

void setup() {
  // put your setup code here, to run once:
  delay(1000);
  Wire.begin(5);
  Wire.onReceive(receiveEvent);
}

void loop() {
  // put your main code here, to run repeatedly:
  cal(Motor_power, Motor_muki);
  Motor_OUTPUT = Motor_power_Send();
  OutPut_Motor(Motor_pin_a, Motor_pin_b, Motor_pin_p, Motor_OUTPUT);
  loopCtrl.Update();
}

void receiveEvent() {
  while (Wire.available()) {
    Motor_power = Wire.read();
    Motor_muki = Wire.read();
  }
}
