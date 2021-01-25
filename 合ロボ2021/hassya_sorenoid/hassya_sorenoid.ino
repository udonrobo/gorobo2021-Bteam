#include<Wire.h>
#include"LoopCycleController.h"

byte Getnumber;
byte output_sorenoid;

LoopCycleController loopCtrl(1000);

void setup() {
  // put your setup code here, to run once:
  delay(1000);
  Wire.begin(1);
  Wire.onReceive(receiveEvent);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(8, output_sorenoid);
  digitalWrite(8, output_sorenoid);
  loopCtrl.Update();
}

void receiveEvent() {
  while (Wire.available()) {
    Getnumber = Wire.read();
  }
  output_sorenoid = bitRead(Getnumber, 0);
}
