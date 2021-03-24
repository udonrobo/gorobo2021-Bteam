#include "Omni.h"
#include "Controller.h"
#include "LoopCycleController.h"
#include "MasterWriter.h"
#include "MasterReader.h"
#include "submaster.h"
#include "Gyro.h"
#include "PidController.h"

bool Air_flag[5];
double asi_No2power[2];

void omni_cal() {
  //  omni.move(DS4.GetLeftxAxis(), DS4.GetLeftyAxis(), DS4.GetRightxAxis());
  ps_LED.SetBitData(1, 0, 1);
  switch (DS4.GetTouchCountUp() % 3) {
    case 0:
      omni.SetMaxPwm(30);
      ps_blue;
      break;
    case 1:
      omni.SetMaxPwm(100);
      ps_yellow();
      break;
    case 2:
      omni.SetMaxPwm(200);
      ps_pink();
      break;
  }

  if (LimitSw.GetBitData(1, 0) && LimitSw.GetBitData(1, 1)) {
    omni.SetMaxPwm(0);
    if (DS4.GetLeftyAxis() < 0)
      omni.SetMaxPwm(15);
  }
}
void stop_omni() {
  if (DS4.GetCrossToggle()) {
    omni.SetMaxPwm(0);
    ps_red();
    tape_red();
    gyro.OffSet_Update();
  }
}

void Send_omni_data() {
  OmniDrive.SetMotorData(1, omni.motorFR());
  OmniDrive.SetMotorData(2, omni.motorFL());
  OmniDrive.SetMotorData(3, omni.motorBL());
  OmniDrive.SetMotorData(4, omni.motorBR());
}

void omni_set() {
  gyro.OffSet_Update();
}

void cal_asiNo2() {

    if (DS4.GetSquareClick()) {
      Air_flag[0] = 1;
      Air_flag[1] = 1;
    }
//  }
  if (DS4.GetL1Click())
    Air_flag[0] = 0;

  if (DS4.GetR1Click())
    Air_flag[1] = 0;

  if (DS4.GetCrossToggle()) {
    asi_No2power[0] = constrain(DS4.GetLeftyAxis(), 0, 0);
    asi_No2power[1] = constrain(DS4.GetLeftyAxis(), 0, 0);
  }
  else {
    asi_No2power[0] = constrain(DS4.GetLeftyAxis(), -50, 50);
    asi_No2power[1] = constrain(DS4.GetLeftyAxis(), -50, 50);
  }
}

void send_asiNo2() {
  if (Air_flag[0] || Air_flag[1]) {
    motor1.SetMotorData(1, -asi_No2power[0]);
    motor1.SetMotorData(2, asi_No2power[1]);
  }
  Air.SetBitData(1, 0, Air_flag[0]); //flont
  Air.SetBitData(1, 1, Air_flag[1]); //rear
}

void show_asi() {
  Serial.print(Air_flag[0]); Serial.print("\t");
  Serial.print(Air_flag[1]); Serial.print("\t");
  Serial.print(asi_No2power[0]); Serial.print("\t");
  Serial.print(asi_No2power[1]); Serial.print("\t");
  Serial.print(omni.motorFR()); Serial.print("\t");
  Serial.print(omni.motorFL()); Serial.print("\t");
  Serial.print(omni.motorBL()); Serial.print("\t");
  Serial.print(omni.motorBR()); Serial.print("\t");
}
