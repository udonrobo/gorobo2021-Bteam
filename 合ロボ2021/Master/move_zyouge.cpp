#include<arduino.h>
int paturn_zyouge;
const int switch_front_left_body = 10;
const int switch_front_right_body = 11;
const int switch_front = 12;
const int switch_back = 13;

byte omuni_power1_zyouge_send;
byte omuni_power2_zyouge_send;
byte omuni_power3_zyouge_send;
byte omuni_power4_zyouge_send;
byte omuni_muki_zyouge_send;
byte airsirinder_zyouge_send;
byte reset_count;
void move_zyouge() {
  pinMode(switch_front_left_body, INPUT_PULLUP);
  pinMode(switch_front_right_body, INPUT_PULLUP) ;
  pinMode(switch_front , INPUT_PULLUP);
  pinMode(switch_back , INPUT_PULLUP);

  switch (paturn_zyouge) {
    case 0://最初、エアシリンダーを伸ばす。エアシリンダーは、1モーター、2前、3後ろ
      omuni_power1_zyouge_send = 0;
      omuni_power1_zyouge_send = 0;
      omuni_power1_zyouge_send = 0;
      omuni_power1_zyouge_send = 0;
      omuni_muki_zyouge_send = 0;
      airsirinder_zyouge_send = 6;
      reset_count = 1;
      break;
    case 1://エアシリンダーを伸ばしたまま前に進む。前に進むときのオムニの符号は9
      omuni_power1_zyouge_send = 36;
      omuni_power1_zyouge_send = 36;
      omuni_power1_zyouge_send = 36;
      omuni_power1_zyouge_send = 36;
      omuni_muki_zyouge_send = 9;
      airsirinder_zyouge_send = 7;
      reset_count = 1;
      break;
    case 3://前のエアシリンダーを引っ込める
      omuni_power1_zyouge_send = 0;
      omuni_power1_zyouge_send = 0;
      omuni_power1_zyouge_send = 0;
      omuni_power1_zyouge_send = 0;
      omuni_muki_zyouge_send = 0;
      airsirinder_zyouge_send = 4;
      reset_count = 1;
      break;
    case 4://前のエアシリンダーを縮め、後ろを伸ばしたまま前に進む
      omuni_power1_zyouge_send = 36;
      omuni_power1_zyouge_send = 36;
      omuni_power1_zyouge_send = 36;
      omuni_power1_zyouge_send = 36;
      omuni_muki_zyouge_send = 9;
      airsirinder_zyouge_send = 5;
      reset_count = 1;
      break;
    case 5://後ろのエアシリンダーを引っ込める
      omuni_power1_zyouge_send = 0;
      omuni_power1_zyouge_send = 0;
      omuni_power1_zyouge_send = 0;
      omuni_power1_zyouge_send = 0;
      omuni_muki_zyouge_send = 0;
      airsirinder_zyouge_send = 0;
      reset_count = 0;
      break;
  }
}
byte omuni_power1_zyouge() {
  return omuni_power1_zyouge_send;
}
byte omuni_power2_zyouge() {
  return omuni_power1_zyouge_send;
}
byte omuni_power3_zyouge() {
  return omuni_power1_zyouge_send;
}
byte omuni_power4_zyouge() {
  return omuni_power1_zyouge_send;
}
byte omuni_muki_zyouge() {
  return omuni_muki_zyouge_send;
}
byte airsirinder_zyouge() {
  return airsirinder_zyouge_send;
}
byte reset_move() {
  return reset_count;
}
