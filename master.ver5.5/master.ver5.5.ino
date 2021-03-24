#include "Omni.h"
#include "Controller.h"
#include "LoopCycleController.h"
#include "MasterWriter.h"
#include "MasterReader.h"
#include "submaster.h"
#include "Gyro.h"
#include "PidController.h"
#include "enc_board_teensy.h"

const int Air_address = 1;
const int OmniDrive_address = 2;
const int motor1_address = 3;
const int motor2_address = 4;
const int servo_address = 5;
const int Controller_Address = 6;
const int LED_address = 7;
const int enc_address = 8;
const int LimitSw_address = 10;

ControllerManager DS4(Controller_Address);
LoopCycleController loopCtrl(5000);
MasterWriter OmniDrive(OmniDrive_address, 5);
MasterWriter motor1(motor1_address, 5), motor2(motor2_address, 5);
MasterWriter ps_LED(Controller_Address, 4), tape_LED(LED_address, 4);
MasterWriter Air(Air_address, 1), servo(servo_address, 5);
MasterReader LimitSw(LimitSw_address, 1);
Gyro gyro;
PidController gyro_pid(3.0, 0, 0.18, loopCtrl.Cycle_us(), 300.0);
PidController shouko_pid(3.0, 9, 0.18, loopCtrl.Cycle_us(), 300.0);
PidController nae_moveX_pid(12.0, 0, 0.2, loopCtrl.Cycle_us(), 300.0);
EncoderBoardTeensy enc1(enc_address);
Omni omni(0,100);

bool se = 1;

void setup() {
  delay(3000);
  Wire.begin();
  Serial.begin(115200);
  //  Serial1.begin(115200);
  enc1.init();
}

void loop() {
  start_Update();

  ps_blue();

    if (se) {
      omni_set();
      nae_set();
      set_shouko();
      if (DS4.GetLeftyAxis() || DS4.GetLeftxAxis())
        se = 0;
    }
    if (DS4.GetStartClick())
      se = 1;

  Omnigyro();
  omni_cal();
  gyro.GyroCaluculate();  
  cal_nae_move();
  cal_shouko();
  if (!DS4.GetCrossToggle()){
    cal_asiNo2();
    cal_nae_catch();
    cal_hana_catch();
  }

  stop_omni();  
  stop_nae();
  stop_shouko();

  Send_omni_data();
  send_asiNo2();
  send_hana();
  send_nae();
  send_shouko();

  show();

  end_Update();
}

void show() {
//    LimitSw.read_show();
  //  gyro_power();
  //  gyro.gyro_show();
  //    OmniDrive.show();
  //  motor1.show();
    motor2.show();
  //      show_asi();
  //  hana_show();
      show_nae();
//  show_shouko();
  Serial.println();
}
