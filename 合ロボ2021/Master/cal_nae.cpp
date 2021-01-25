#include<arduino.h>
#include"PidController.h"
#include"enc_board_mbed.h"

PidController pid_nae_kankaku (7, 0, 0.2, 10000, 300.0);
EncoderBoardMbed enc_nae_kankaku(15);

const int switch_pin_ue = 4;//機構の上下(上)
const int switch_pin_sita = 5;//機構の上下(下)
const int switch_pin_long = 6;//前後の確認ピン(伸びきったほう)
const int switch_pin_short = 7;//前後の確認ピン(縮んだほう)
const int switch_pin_reset = 8;//間隔
const int encorder_port = 2;

byte Motor_power_nae_zengo_cal;
byte Motor_muki_nae_zengo_cal;
byte Motor_power_zyouge_cal;
byte Motor_muki_zyouge_cal;
byte Motor_power_kankaku_cal;
byte Motor_muki_kankaku_cal;
byte Motor_power_kankaku_send;
byte Motor_muki_kankaku_send;
byte Motor_muki_send;
byte set_reset;

void cal_nae(byte zyouge, byte kankaku, byte oshidasi, byte kaisyuu) {
  pinMode(switch_pin_long, INPUT_PULLUP);//前後
  pinMode(switch_pin_short, INPUT_PULLUP);//前後
  pinMode(switch_pin_reset, INPUT_PULLUP);//間隔
  pinMode(switch_pin_ue, INPUT_PULLUP);//上下
  pinMode(switch_pin_sita, INPUT_PULLUP);//上下
  //前後
  if (oshidasi == 0) {
    if (switch_pin_short == LOW) {
      Motor_power_nae_zengo_cal = 0;
    } else {
      Motor_power_nae_zengo_cal = 30;
      Motor_muki_nae_zengo_cal = 1;
    }
  } else {
    if (switch_pin_long == LOW) {
      Motor_power_nae_zengo_cal = 0;
    } else {
      Motor_power_nae_zengo_cal = 30;
      Motor_muki_nae_zengo_cal = 0;
    }
  }
  //上下
  if (zyouge == 0) {
    if (switch_pin_sita == LOW) {
      Motor_power_zyouge_cal = 0;
    } else {
      Motor_power_zyouge_cal = 30;
      Motor_muki_zyouge_cal = 1;
    }
  } else {
    if (switch_pin_ue == LOW) {
      Motor_power_zyouge_cal = 0;
    } else {
      Motor_power_zyouge_cal = 30;
      Motor_muki_zyouge_cal = 0;
    }
  }
  //間隔
  enc_nae_kankaku.Update();
  if (set_reset == 0) {
    Motor_power_kankaku_send = 25;
    Motor_muki_kankaku_send = 1;
    if (digitalRead(switch_pin_reset) == LOW) {
      set_reset = 1;
    }
  } else {
    if (kankaku == 0) {
      pid_nae_kankaku.Update(PI * 29 * enc_nae_kankaku.getCount(encorder_port) / 4096, 0);
    } else {
      pid_nae_kankaku.Update(PI * 29 * enc_nae_kankaku.getCount(encorder_port) / 4096, 100);
    }
    Motor_power_kankaku_cal = constrain(pid_nae_kankaku.GetPower(), -80, 80);
    if (Motor_power_kankaku_cal < 0) {
      Motor_power_kankaku_send = abs(Motor_power_kankaku_send);
      Motor_muki_kankaku_send = 1;
    } else {
      Motor_power_kankaku_send = abs(Motor_power_kankaku_send);
      Motor_muki_kankaku_send = 0;
    }
  }
  //上下、間隔、前後、エアシリンダー
  bitWrite(Motor_muki_send,0,Motor_muki_zyouge_cal);
  bitWrite(Motor_muki_send,1,Motor_muki_kankaku_send);
  bitWrite(Motor_muki_send,2,Motor_muki_nae_zengo_cal);
  bitWrite(Motor_muki_send,3,kaisyuu);
}

byte Motor_power_nae_zyouge_return() {
  return Motor_power_zyouge_cal;
}
byte Motor_power_nae_zengo_return() {
  return Motor_power_nae_zengo_cal;
}
byte Motor_power_kankaku_return() {
  return Motor_power_kankaku_send;
}
byte Motor_muki_return() {
return Motor_muki_send;
}
