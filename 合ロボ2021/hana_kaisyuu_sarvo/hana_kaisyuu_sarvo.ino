#include<Wire.h>  //
#include<Servo.h>
#include"LoopCycleController.h"
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
LoopCycleController loopCtrl(1000);
byte Getnumber;
void setup() {
  // put your setup code here, to run once:
  delay(1000);
  Wire.begin(8);
  servo1.attach(5);
  servo1.attach(6);
  servo1.attach(9);
  servo1.attach(10);
  Wire.onReceive(receiveEvent);
}

void loop() {
  // put your main code here, to run repeatedly:
  servo1.write(Getnumber);
  servo2.write(Getnumber);
  servo3.write(Getnumber);
  servo4.write(Getnumber);
  loopCtrl.Update();
}
void receiveEvent() {
  while (Wire.available()) {
    Getnumber = Wire.read();
  }
}
