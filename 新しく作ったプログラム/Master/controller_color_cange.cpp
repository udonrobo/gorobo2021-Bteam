#include<arduino.h>
byte LED_Red;
byte LED_Green;
byte LED_Blue;

void color_cange_controller(byte color) {
  switch (color) {
    case 0:
      LED_Red = 100;
      LED_Green = 0;
      LED_Blue = 0;
      break;
    case 1:
      LED_Red = 0;
      LED_Green = 0;
      LED_Blue = 100;
      break;
  }
}
//光らすか、R、G、B
byte color1_return() {
  return LED_Red;
}
byte color2_return() {
  return LED_Green;
}
byte color3_return() {
  return LED_Blue;
}
