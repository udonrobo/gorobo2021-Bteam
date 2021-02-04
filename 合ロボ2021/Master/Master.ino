#include<Wire.h>
#include"subMaster.h"
#include"LoopCycleController.h"

LoopCycleController loopCtrl(10000);
//昇降の上2、下が3
//苗木の上にあげる、上が4、下が5
//苗木の押出、出きった方が6、引っ込んだほうが7
//間隔8,9
//段差越え、車体の左10、右11、エアシリンダーの前12、後13
const int switch_front_left_body=10;
const int switch_front_right_body=11;

byte Motor_power_omuni_Get[3];
byte Syoukou_Get;
byte zyouge_Get;
byte naekaisyuu_Get;
byte syoukou_Get;
byte hassya_Get;
byte hanakaisyuu_Get;
byte nae_oshidasi_Get;
byte nae_zyouge_Get;
byte nae_kankaku_Get;
byte Gyro_reset_Get;
byte Motor_power_air_serinder;
byte Motor_power_omuni_Send[5];
byte Syoukou_Send;
byte zyouge_Send;
byte naekaisyuu_Send;
byte syoukou_Send;
byte hassya_Send;
byte hanakaisyuu_Send;
byte stop_bottun;
byte toggle_syoukou;
byte toggle_naekaisyuu;
byte toggle_stop;
byte toggle_hanakaisyuu;
byte Motor_power_syoukou_Send;
byte Motor_muki_syoukou;
byte Slave_Send_Motor_power_zyouge;
byte Slave_Send_Motor_power_kankaku;
byte Slave_Send_Motor_power_zengo;
byte Slave_Send_Motor_muki;
int a;

void setup() {
  // put your setup code here, to run once:
  delay(1000);
  Wire.begin();
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  Get_number();
  hanakaisyuu_Get = controller_bottun_L2();//花回収(L2)
  naekaisyuu_Get = controller_bottun_R2();//苗回収(R2)
  syoukou_Get = controller_bottun_R1();//昇降(R1)
  nae_oshidasi_Get = controller_bottun_L1();//苗の押出(L1)
  nae_zyouge_Get = controller_bottun_sikaku();//苗の上下(□)
  nae_kankaku_Get = controller_bottun_sankaku();//苗の間隔(△)
  Gyro_reset_Get = controller_bottun_maru();//ジャイロのリセット(〇)
  stop_bottun = controller_bottun_batu();//非常停止(×)
  Motor_power_omuni_Get[0] = controller_left_X();//移動のX座標(左スティックX)
  Motor_power_omuni_Get[1] = controller_left_Y();//移動のY座標(左スティックY)
  Motor_power_omuni_Get[2] = controller_right_X();//旋回(右スティックX)

  if (digitalRead(switch_front_left_body) == LOW || digitalRead(switch_front_right_body) == LOW) {
    a = 1;//スイッチが押された=段差にぶつかったとき
  }
  toggle_R1(syoukou_Get);
  toggle_R2(naekaisyuu_Get);
  toggle_L1(nae_oshidasi_Get);
  toggle_L2(hanakaisyuu_Get);
  toggle_sankaku(nae_kankaku_Get);
  toggle_sikaku(nae_zyouge_Get);
  click_maru(Gyro_reset_Get);
  toggle_batu(stop_bottun);

  hanakaisyuu_Get = toggle_Send_L2() ;
  naekaisyuu_Get = toggle_Send_R2();
  syoukou_Get = toggle_Send_R1();
  nae_oshidasi_Get = toggle_Send_L1();
  nae_kankaku_Get = toggle_Send_sankaku();
  nae_zyouge_Get = toggle_Send_sikaku();
  Gyro_reset_Get = click_Send_maru();
  stop_bottun = toggle_Send_batu() ;
  if (a == 0) {
    cal_omuni(Motor_power_omuni_Get[0], Motor_power_omuni_Get[1], Motor_power_omuni_Get[2], Gyro_power());
    cal_Servo(hanakaisyuu_Get);
    cal_syoukou(syoukou_Get * stop_bottun);
    cal_nae(nae_zyouge_Get, nae_kankaku_Get, nae_oshidasi_Get, naekaisyuu_Get);

    Gyro_cal(Motor_power_omuni_Get[2], stop_bottun, Gyro_reset_Get);

    Motor_power_omuni_Send[0] = Motor_power_omuni_1() * stop_bottun;
    Motor_power_omuni_Send[1] = Motor_power_omuni_2() * stop_bottun;
    Motor_power_omuni_Send[2] = Motor_power_omuni_3() * stop_bottun;
    Motor_power_omuni_Send[3] = Motor_power_omuni_4() * stop_bottun;
    Motor_power_omuni_Send[4] = Motor_power_omuni_Send_muki();

    Motor_power_syoukou_Send = Motor_power_shoukou() * stop_bottun;
    Motor_muki_syoukou = Motor_muki_shoukou() * stop_bottun;

    Slave_Send_Motor_power_zyouge = Motor_power_nae_zyouge_return() * stop_bottun;
    Slave_Send_Motor_power_kankaku = Motor_power_nae_zengo_return() * stop_bottun;
    Slave_Send_Motor_power_zengo = Motor_power_kankaku_return() * stop_bottun;
    Slave_Send_Motor_muki = Motor_muki_return();

    Slave_Send_omuni(Motor_power_omuni_Send[0], Motor_power_omuni_Send[1], Motor_power_omuni_Send[2], Motor_power_omuni_Send[3], Motor_power_omuni_Send[4]);
    Slave_Send_syoukou(Motor_power_syoukou_Send, Motor_muki_syoukou);
    Slave_Send_dansa(0);
    Slave_Send_hanakaisyuu(Servo_kakudo());
    Slave_Send_nae(Slave_Send_Motor_power_zyouge, Slave_Send_Motor_power_kankaku, Slave_Send_Motor_power_zengo, Slave_Send_Motor_muki);

    Serial.print(Motor_power_omuni_Send[0]); Serial.print("\t");
    Serial.print(Motor_power_omuni_Send[1]); Serial.print("\t");
    Serial.print(Motor_power_omuni_Send[2]); Serial.print("\t");
    Serial.print(Motor_power_omuni_Send[3]); Serial.print("\t");
    Serial.print(Motor_power_omuni_Send[4]); Serial.print("\t");
    Serial.print(hanakaisyuu_Get); Serial.print("\t");
    Serial.print(naekaisyuu_Get); Serial.print("\t");
    Serial.print(syoukou_Get); Serial.print("\t");
    Serial.print(stop_bottun); Serial.print("\t");
    Serial.println();
  } else {
    move_zyouge();
    Motor_power_omuni_Send[0] = omuni_power1_zyouge();
    Motor_power_omuni_Send[1] = omuni_power2_zyouge();
    Motor_power_omuni_Send[2] = omuni_power3_zyouge();
    Motor_power_omuni_Send[3] = omuni_power4_zyouge();
    Motor_power_omuni_Send[4] = omuni_muki_zyouge();
    Slave_Send_omuni(Motor_power_omuni_Send[0], Motor_power_omuni_Send[1], Motor_power_omuni_Send[2], Motor_power_omuni_Send[3], Motor_power_omuni_Send[4]);
    Slave_Send_dansa(airsirinder_zyouge());
    a = reset_move();
  }
  loopCtrl.Update();
}
