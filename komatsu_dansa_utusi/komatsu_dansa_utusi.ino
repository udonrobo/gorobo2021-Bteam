#include <Wire.h>
#include "LoopCycleController.h"
#include "Motor.h"
#include "MovingAverage.h"

int zenyomi;
int motoyomi;
int JALfro;
int JALbac;

const int ANA1 = 1;
const int ANA2 = 2;

motor motorK(8, 10, 9);
motor motorN(12, 13, 11);
LoopCycleController loopCtrl(10000);
MovingAverage average1(100), average2(100);

void setup() {
  pinMode(ANA1, OUTPUT);
  pinMode(ANA2, OUTPUT);
  delay(1000);

  Wire.begin(3);
  Wire.onReceive(receiveEvent);

  Serial.begin(115200);
}

void loop() {
  if (JALfro > 0) {
    digitalWrite(ANA1, HIGH);
  }
  else {
    digitalWrite(ANA1, LOW);
  }
  if (JALbac > 0) {
    digitalWrite(ANA2, HIGH);
  }
  else {
    digitalWrite(ANA2, LOW);
  }
  maware();
  average1.Update(motomawasi());
  average2.Update(motomawasi());
  motorK.motor_move(average1.GetValue());
  motorN.motor_move(average2.GetValue());
  motorK.show_motor();
  motorN.show_motor();
  Serial.println();
  loopCtrl.Update();
}

void receiveEvent(int ShutupFucker) {
  while (Wire.available()) {
    zenyomi = Wire.read();
    motoyomi = bitRead(zenyomi, 0);
    JALfro = bitRead(zenyomi, 1);
    JALbac = bitRead(zenyomi, 2);
  }
}

void maware () {
  if (motoyomi > 0) {
    motoyomi = 80;
  }
  else motoyomi = 0;
}

int motomawasi() {
  return motoyomi;
}
