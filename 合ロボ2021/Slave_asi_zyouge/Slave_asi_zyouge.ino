#include<Wire.h>
#include"LoopCycleController.h"
#include"MovingAverage.h"
#include"subMaster.h"

LoopCycleController loopCtrl(1000);
MovingAverage average(100);
byte Getnumber;
int Motor_power;
byte airSerinder_front;
byte airSerinder_back;

void setup() {
  // put your setup code here, to run once:
  delay(1000);
  Wire.begin(7);
  Wire.onReceive(receiveEvent);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (bitRead(Getnumber,0) == 0) {
    Motor_power = 0;
  } else {
    Motor_power = 62;
  }
  average.Update(Motor_power);
  airSerinder_front=bitRead(Getnumber,1);
  airSerinder_back=bitRead(Getnumber,2);
  output(Motor_power,airSerinder_front ,airSerinder_back);
}

void receiveEvent() {
  while (Wire.available()) {
    Getnumber = Wire.read();
  }
}
