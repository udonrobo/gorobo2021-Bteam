#include "Controller.h"
#include "MasterWriter.h"
#include "MasterReader.h"
#include "enc_board_teensy.h"
#include "PidController.h"
#include "submaster.h"

double motor_x_power;
double motor_y_power;
double motor_z_power;

//int i = false;
//bool z_flag, z_flag2;
bool set_y_flag;

//int Arm_L = 2, Arm_C = 3, Arm_R = 4;
int Arm;

void cal_nae_catch() { //ボタン一つでいいってよ
  Arm = DS4.GetCircleToggle();
}

void cal_nae_move() {
  //      motor_x_power = 0;
  //  motor_y_power = 0;
  //  motor_z_power = 0;


  if (DS4.GetRightCountUp() > 0) {
    switch (DS4.GetRightCountUp() % 3) {
      case 0:
        //          motor_x_power = 0;
        nae_moveX_pid.Update(PI * 30 * enc1.getCount(2) / 8192, 0);
        break;
      case 1:
        //          motor_x_power = 50;
        nae_moveX_pid.Update(PI * 30 * enc1.getCount(2) / 8192, 120);
//        if (LimitSw.GetBitData(1, 4))
//          nae_moveX_pid.Update(PI * 30 * enc1.getCount(2) / 8192, 180);
        break;
      case 2:
        //          motor_x_power = -50;
        nae_moveX_pid.Update(PI * 30 * enc1.getCount(2) / 8192, 180);
        break;
    }
    motor_x_power = -constrain(nae_moveX_pid.GetPower(), -100, 100);
    if (LimitSw.GetBitData(1, 2) && motor_x_power > 0)
      motor_x_power = 0;
  }


  if (set_y_flag)
    motor_y_power = DS4.GetR2() && !LimitSw.GetBitData(1, 3) ? 150 : DS4.GetUp() && !LimitSw.GetBitData(1, 4) ? -150 : 0;


  //  motor_z_power = DS4.GetLeftCountUp() % 2 ? 45 : (DS4.GetLeftCountUp() % 3) - 1 ? 180 : 0;
  motor_z_power = DS4.GetLeftCountUp() % 2 ? 180 : 0;

}

void stop_nae() {
  if (DS4.GetCrossToggle()) {
    Air.SetBitData(1, 2, 0);
    Air.SetBitData(1, 3, 0);
    motor_x_power = 0;
    motor_y_power = 0;
  }
}

void send_nae() {
  Air.SetBitData(1, 3, Arm);
  motor2.SetMotorData(2, motor_x_power);
  motor2.SetMotorData(3, motor_y_power);
  servo.SetSingleData(5, motor_z_power);
}

void nae_set() {
  motor_x_power = 50;
  if (LimitSw.GetBitData(1, 2)) {
    motor_x_power = 0;
    enc1.resetCount(2);
  }
  motor_y_power = 50;
  if (LimitSw.GetBitData(1, 3)) {
    motor_y_power = 0;
    set_y_flag = true;
  }
  motor_z_power = 180;
}

void show_nae() {
  Serial.print(nae_moveX_pid.GetPower()); Serial.print("\t");
  Serial.print(DS4.GetRightCountUp() % 3); Serial.print("\t");
  Serial.print(PI * 30 * enc1.getCount(2) / 8192); Serial.print("\t");
  //  Serial.print(enc1.getCount(2)); Serial.print("\t");
  //  Serial.print(set_x_flag); Serial.print("\t");
  //  Serial.print(set_z_flag); Serial.print("\t");
  Serial.print(motor_x_power); Serial.print("\t");
  //  Serial.print(motor_y_power); Serial.print("\t");
  //  Serial.print(motor_z_power); Serial.print("\t");
  //  Serial.print(Arm); Serial.print("\t");
}
