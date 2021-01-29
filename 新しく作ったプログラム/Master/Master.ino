#include<Wire.h>
#include"subMaster.h"
#include"LoopCycleController.h"
#include"MasterWriter.h"
#include"Controller.h"

const int Controller_address = 6;
const int Omni_address = 3;
const int nae_address = 4;
const int syoukou_address = 5;
const int zyouge_address = 7;
const int hana_address = 8;

const int switch_front_left_body = 10;
const int switch_front_right_body = 11;

ControllerManager DS4(Controller_address);
MasterWriter OmniDrive(Omni_address, 5);
MasterWriter naeDrive(nae_address, 4);
MasterWriter shoukouDrive(syoukou_address, 5);
MasterWriter zyougeDrive(zyouge_address, 7);
MasterWriter hanaDrive(hana_address, 8);
MasterWriter PSbutton (Controller_address, 4);

LoopCycleController loopCtrl(10000);

//昇降の上2、下が3
//苗木の上にあげる、上が4、下が5
//苗木の押出、出きった方が6、引っ込んだほうが7
//間隔8,9
//段差越え、車体の左10、右11、エアシリンダーの前12、後13

int Motor_power_omuni_Get[3];
byte zyouge_Get;
byte naekaisyuu_Get;
byte syoukou_Get;
byte hassya_Get;
byte hanakaisyuu_Get;
byte nae_oshidasi_Get;
byte nae_zyouge_Get;
byte nae_kankaku_Get;
byte Gyro_reset_Get;
byte stop_bottun;

byte Motor_power_syoukou_Send;//
byte Motor_muki_syoukou_Send;//
byte nae_motor_muki_Send;//
byte hanakaisyuu_Send;//
byte Motor_power_omuni_Send[5];//
byte Slave_Send_Motor_power_zyouge;//
byte Slave_Send_Motor_power_kankaku;//
byte Slave_Send_Motor_power_zengo;//
byte Slave_Send_Motor_muki;//
byte Slave_Send_air_Sirinder;//
byte a;

void setup() {
  // put your setup code here, to run once:
  delay(1000);
  Wire.begin();
  Serial.begin(115200);
  pinMode(switch_front_left_body, INPUT_PULLUP);
  pinMode(switch_front_right_body, INPUT_PULLUP);
}
void loop() {
  DS4.Update();
  PSbutton.Update();
  shoukouDrive.Update();
  hanaDrive.Update();
  OmniDrive.Update();
  naeDrive.Update();
  zyougeDrive.Update();

  // put your main code here, to run repeatedly:
  nae_oshidasi_Get = DS4.GetL1Toggle();//苗の押出(L1)
  syoukou_Get = DS4.GetR1Toggle();//昇降(R1)
  hanakaisyuu_Get = DS4.GetL2Toggle();//花回収(L2)
  naekaisyuu_Get = DS4.GetR2Toggle();//苗回収(R2)
  nae_zyouge_Get = DS4.GetSquareToggle();//苗の上下(□)
  nae_kankaku_Get = DS4.GetTriangleToggle();//苗の間隔(△)
  Gyro_reset_Get = DS4.GetCircleClick();//ジャイロのリセット(〇)
  stop_bottun = DS4.GetCrossToggle();//非常停止(×)
  Motor_power_omuni_Get[0] = DS4.GetLeftxAxis();//移動のX座標(左スティックX)
  Motor_power_omuni_Get[1] = DS4.GetLeftyAxis();//移動のY座標(左スティックY)
  Motor_power_omuni_Get[2] = DS4.GetRightxAxis();//旋回(右スティックX)
  color_cange_controller(stop_bottun);

  //  if (digitalRead(switch_front_left_body) == LOW || digitalRead(switch_front_right_body) == LOW) {
  //    a = 1;//スイッチが押された=段差にぶつかったとき
  //  }
  if (a == 0) {
    //計算
    cal_omuni(Motor_power_omuni_Get[0], Motor_power_omuni_Get[1], Motor_power_omuni_Get[2], Gyro_power());
    cal_Servo(hanakaisyuu_Get);
    cal_syoukou(syoukou_Get * stop_bottun);
    cal_nae(nae_zyouge_Get, nae_kankaku_Get, nae_oshidasi_Get, naekaisyuu_Get);
    Gyro_cal(Motor_power_omuni_Get[2], stop_bottun, Gyro_reset_Get);
    //代入
    //オムニ
    Motor_power_omuni_Send[0] = Motor_power_omuni_1() * stop_bottun;
    Motor_power_omuni_Send[1] = Motor_power_omuni_2() * stop_bottun;
    Motor_power_omuni_Send[2] = Motor_power_omuni_3() * stop_bottun;
    Motor_power_omuni_Send[3] = Motor_power_omuni_4() * stop_bottun;
    Motor_power_omuni_Send[4] = Motor_power_omuni_Send_muki();
    //昇降
    Motor_power_syoukou_Send = Motor_power_shoukou() * stop_bottun;
    Motor_muki_syoukou_Send = Motor_muki_shoukou() * stop_bottun;
    //苗
    Slave_Send_Motor_power_zyouge = Motor_power_nae_zyouge_return() * stop_bottun;
    Slave_Send_Motor_power_kankaku = Motor_power_nae_zengo_return() * stop_bottun;
    Slave_Send_Motor_power_zengo = Motor_power_kankaku_return() * stop_bottun;
    Slave_Send_Motor_muki = Motor_muki_return();
    Slave_Send_air_Sirinder = 0;//
    //Serialプリント
    Serial.print(Motor_power_omuni_Send[0]); Serial.print("\t");
    Serial.print(Motor_power_omuni_Send[1]); Serial.print("\t");
    Serial.print(Motor_power_omuni_Send[2]); Serial.print("\t");
    Serial.print(Motor_power_omuni_Send[3]); Serial.print("\t");
    Serial.print(Motor_power_omuni_Send[4]); Serial.print("\t");
    Serial.print(hanakaisyuu_Get); Serial.print("\t");
    Serial.print(naekaisyuu_Get); Serial.print("\t");
    Serial.print(syoukou_Get); Serial.print("\t");
    Serial.print(stop_bottun); Serial.print("\t");
    Serial.print(color1_return()); Serial.print("\t");
    Serial.print(color2_return()); Serial.print("\t");
    Serial.print(color3_return()); Serial.print("\t");
    Serial.print(Gyro_power()); Serial.print("\t");
    Serial.println();
  } else {//段差を登る
    move_zyouge(stop_bottun);
    Slave_Send_Motor_power_zyouge = 0;//
    Slave_Send_Motor_power_kankaku = 0;//
    Slave_Send_Motor_power_zengo = 0;//
    Slave_Send_Motor_muki = 0;//
    Motor_power_omuni_Send[0] = omuni_power1_zyouge();
    Motor_power_omuni_Send[1] = omuni_power2_zyouge();
    Motor_power_omuni_Send[2] = omuni_power3_zyouge();
    Motor_power_omuni_Send[3] = omuni_power4_zyouge();
    Motor_power_omuni_Send[4] = omuni_muki_zyouge();
    Slave_Send_air_Sirinder = airsirinder_zyouge();
    a = reset_move();
  }
  PSbutton.SetBitData(1, 0, 1);
  PSbutton.SetSingleData(2, color1_return());
  PSbutton.SetSingleData(3, color2_return());
  PSbutton.SetSingleData(4, color3_return());
  
  shoukouDrive.SetSingleData(1, Motor_power_syoukou_Send); //
  shoukouDrive.SetSingleData(2, Motor_muki_syoukou_Send); //
  hanaDrive.SetSingleData(1, hanakaisyuu_Send); //
  OmniDrive.SetSingleData(1, Motor_power_omuni_Send[0]); //
  OmniDrive.SetSingleData(2, Motor_power_omuni_Send[1]); //
  OmniDrive.SetSingleData(3, Motor_power_omuni_Send[2]); //
  OmniDrive.SetSingleData(4, Motor_power_omuni_Send[3]); //
  OmniDrive.SetSingleData(5, Motor_power_omuni_Send[4]); //
  naeDrive.SetSingleData(1, Slave_Send_Motor_power_zyouge); //
  naeDrive.SetSingleData(2, Slave_Send_Motor_power_kankaku); //
  naeDrive.SetSingleData(3, Slave_Send_Motor_power_zengo); //
  naeDrive.SetSingleData(4, Slave_Send_Motor_muki); //
  zyougeDrive.SetSingleData(1, Slave_Send_air_Sirinder); //
  loopCtrl.Update();
}
