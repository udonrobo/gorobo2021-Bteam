#include<Wire.h>
#include"subMaster.h"
#include"LoopCycleController.h"
byte Getnumber[4];
byte air_output;
byte Motor_power_nae_zyouge;
byte Motor_muki_nae_zyouge;

byte Motor_power_nae_oshidasi;
byte Motor_muki_nae_oshidasi;

byte Motor_power_nae_kankaku;
byte Motor_muki_nae_kankaku;

const int motor_up_pin_a = 2;
const int motor_up_pin_b = 3;
const int motor_up_pin_p = 4;
//2
const int nae1_pin = 5;
const int nae2_pin = 6;
const int nae3_pin = 7;
//1
const int nae_kankaku_motor_pin_a = 8;
const int nae_kankaku_motor_pin_b = 9;
const int nae_kankaku_motor_pin_p = 10;
//2
const int nae_oshidasi_motor_pin_a = 11;
const int nae_oshidasi_motor_pin_b = 12;
const int nae_oshidasi_motor_pin_p = 13;
//2
LoopCycleController loopCtrl(1000);
void setup() {
  // put your setup code here, to run once:
  delay(1000);
  Wire.begin(4);
  Wire.onReceive(receiveEvent);
  pinMode(nae1_pin, OUTPUT);//苗1
  pinMode(nae2_pin, OUTPUT);//苗2
  pinMode(nae3_pin, OUTPUT);//苗3
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(8, air_output);
  digitalWrite(9, air_output);
  digitalWrite(10, air_output);
  //  motor_OUTPUT(a,b,p,Motor_power,Motor_muki)
  motor_OUTPUT(motor_up_pin_a, motor_up_pin_b, motor_up_pin_p, Motor_power_nae_zyouge, Motor_muki_nae_zyouge);
  motor_OUTPUT(nae_kankaku_motor_pin_a, nae_kankaku_motor_pin_b, nae_kankaku_motor_pin_p, Motor_power_nae_kankaku, Motor_muki_nae_kankaku);
  motor_OUTPUT(nae_oshidasi_motor_pin_a, nae_oshidasi_motor_pin_b, nae_oshidasi_motor_pin_p, Motor_power_nae_oshidasi, Motor_muki_nae_oshidasi);
  loopCtrl.Update();
}

void receiveEvent() {
  while (Wire.available()) {
    Getnumber[0] = Wire.read();
    //機構を上にあげるモーターのパワー
    Getnumber[1] = Wire.read();
    //苗の間隔を変えるモーターのパワー
    Getnumber[2] = Wire.read();
    //苗を押し出すモーターのパワー
    Getnumber[3] = Wire.read();
    //機構を上にあげるモーターの回転方向、苗の間隔を変えるモーターの回転方向、苗を押し出すモーターの回転方向、エアシリンダーを出すか引っ込めるか
  }
  Motor_power_nae_zyouge = Getnumber[0];
  Motor_power_nae_kankaku = Getnumber[1];
  Motor_power_nae_oshidasi = Getnumber[2];
  Motor_muki_nae_zyouge = bitRead(Getnumber[3], 0);
  Motor_muki_nae_kankaku = bitRead(Getnumber[3], 1);
  Motor_muki_nae_oshidasi = bitRead(Getnumber[3], 2);
  air_output = bitRead(Getnumber[3], 3);
}
