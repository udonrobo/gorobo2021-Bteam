#include<arduino.h>
byte kakudo_return;

void cal_Servo(byte cal_kakudo) {
  if (cal_kakudo == 0) {
    kakudo_return = 0;
  } else {
    kakudo_return = 45;
  }
}

byte Servo_kakudo() {
  return kakudo_return;
}
