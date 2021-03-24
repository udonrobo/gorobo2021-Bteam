#include "Controller.h"
#include "LoopCycleController.h"
#include "MasterWriter.h"
#include "MasterReader.h"
#include "Gyro.h"
#include "PidController.h"
#include "enc_board_teensy.h"

void start_Update(){
  DS4.Update();
  enc1.update();
  LimitSw.Update();
}

void end_Update(){
  ps_LED.Update();
  OmniDrive.Update();
  motor1.Update();
  motor2.Update();
  ps_LED.Update();
  Air.Update();
  servo.Update();
  loopCtrl.Update();
}
