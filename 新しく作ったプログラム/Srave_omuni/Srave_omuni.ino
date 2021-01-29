#include<Wire.h>
#include"subMaster.h"
#include"LoopCycleController.h"
#include"Movingaverage.h"
LoopCycleController loopCtrl(5000);
MovingAverage average1(100), average2(100), average3(100), average4(100);
int Motor_power[4];
byte Get_number[5];

const int Motor1_pina = 2;
const int Motor1_pinb = 4;
const int Motor1_pinp = 3;

const int Motor2_pina = 5;
const int Motor2_pinb = 6;
const int Motor2_pinp = 9;

const int Motor3_pina = 8;
const int Motor3_pinb = 7;
const int Motor3_pinp = 10;

const int Motor4_pina = 12;
const int Motor4_pinb = 13;
const int Motor4_pinp = 11;

void setup() {
  // put your setup code here, to run once:

  delay(1000);

  Serial.begin(115200);

  Wire.begin(3);
  Wire.onReceive(receiveEvent);
}

void loop() {
  // put your main code here, to run repeatedly:
  cal(Get_number[0], Get_number[1], Get_number[2], Get_number[3], Get_number[4]);

  Motor_power[0] = Motor_power1_back();
  Motor_power[1] = Motor_power1_back();
  Motor_power[2] = Motor_power1_back();
  Motor_power[3] = Motor_power1_back();

  average1.Update(Motor_power[0]);
  average1.Update(Motor_power[1]);
  average1.Update(Motor_power[2]);
  average1.Update(Motor_power[3]);

  Motor_OUTPUT(Motor1_pina, Motor1_pinb, Motor1_pinp, Motor_power[0]);
  Motor_OUTPUT(Motor2_pina, Motor2_pinb, Motor2_pinp, Motor_power[1]);
  Motor_OUTPUT(Motor3_pina, Motor3_pinb, Motor3_pinp, Motor_power[2]);
  Motor_OUTPUT(Motor4_pina, Motor4_pinb, Motor4_pinp, Motor_power[3]);

  Serial.print(Get_number[0]); Serial.print("\t");
  Serial.print(Get_number[1]); Serial.print("\t");
  Serial.print(Get_number[2]); Serial.print("\t");
  Serial.print(Get_number[3]); Serial.print("\t");
  Serial.print(Get_number[4]); Serial.print("\t");
  Serial.print(Motor_power[0]); Serial.print("\t");
  Serial.print(Motor_power[1]); Serial.print("\t");
  Serial.print(Motor_power[2]); Serial.print("\t");
  Serial.print(Motor_power[3]); Serial.print("\t");
  Serial.println();

  loopCtrl.Update();
}

void receiveEvent() {
  while (Wire.available()) {
    Get_number[0] = Wire.read(); //モーター1の回転速度の絶対値
    Get_number[1] = Wire.read(); //モーター2の回転速度の絶対値
    Get_number[2] = Wire.read(); //モーター3の回転速度の絶対値
    Get_number[3] = Wire.read(); //モーター4の回転速度の絶対値
    Get_number[4] = Wire.read(); //モーターの回転方向
  }
}
