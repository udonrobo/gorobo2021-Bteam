#include<arduino.h>
#include<Wire.h>
byte Get_number_controller[9];

void Get_number() {
  Wire.requestFrom(6, 9);
  while (Wire.available()) {
    Get_number_controller[0] = Wire.read();
    Get_number_controller[1] = Wire.read();
    Get_number_controller[2] = Wire.read();
    Get_number_controller[3] = Wire.read();
    Get_number_controller[4] = Wire.read();
    Get_number_controller[5] = Wire.read();
    Get_number_controller[6] = Wire.read();
    Get_number_controller[7] = Wire.read();
    Get_number_controller[8] = Wire.read();
  }
}

byte controller_SHARE() {
  return bitRead(Get_number_controller[0], 0);
}
byte controller_OPTIONS() {
  return bitRead(Get_number_controller[0], 3);
}
byte controller_closs_up() {
  return bitRead(Get_number_controller[0], 4);
}
byte controller_closs_right() {
  return bitRead(Get_number_controller[0], 5);
}
byte controller_closs_down() {
  return bitRead(Get_number_controller[0], 6);
}
byte controller_closs_left() {
  return bitRead(Get_number_controller[0], 7);
}
byte controller_bottun_L2() {
  return bitRead(Get_number_controller[1], 0);
}
byte controller_bottun_R2() {
  return bitRead(Get_number_controller[1], 1);
}
byte controller_bottun_L1() {
  return bitRead(Get_number_controller[1], 2);
}
byte controller_bottun_R1() {
  return bitRead(Get_number_controller[1], 3);
}
byte controller_bottun_sankaku() {
  return bitRead(Get_number_controller[1], 4);
}
byte controller_bottun_maru() {
  return bitRead(Get_number_controller[1], 5);
}
byte controller_bottun_batu() {
  return bitRead(Get_number_controller[1], 6);
}
byte controller_bottun_sikaku() {
  return bitRead(Get_number_controller[1], 7);
}
byte controller_right_X() {
  return Get_number_controller[2];
}
byte controller_right_Y() {
  return Get_number_controller[3];
}
byte controller_left_X() {
  return Get_number_controller[4];
}
byte controller_left_Y() {
  return Get_number_controller[5];
}
