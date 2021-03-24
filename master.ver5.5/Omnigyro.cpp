#include <arduino.h>
#include "Omni.h"
#include "Controller.h"
#include "LoopCycleController.h"
#include "MasterWriter.h"
#include "submaster.h"
#include "Gyro.h"
#include "PidController.h"

int16_t turn_power;
bool set_offsetflag;

void Omnigyro() {
  if (DS4.GetRightxAxis() == 0) {
    if (set_offsetflag) {
      gyro.OffSet_Update();
      static int i;
      i++;
      if (i < 100)
        set_offsetflag = true;
      else if (i >= 100) {
        i = 0;
        set_offsetflag = false;
      }

      omni.move(DS4.GetLeftxAxis(), DS4.GetLeftyAxis(), DS4.GetRightxAxis());
    }
    else {
      gyro.GetGyro();
      gyro_pid.Update(gyro.yaw(), 0);
      turn_power = constrain(gyro_pid.GetPower(), -250, 250);
      omni.move(DS4.GetLeftxAxis(), DS4.GetLeftyAxis(), turn_power * 2);
    }
  }
  else if (abs(DS4.GetRightxAxis()) > 0) {
    set_offsetflag = true;
    omni.move(DS4.GetLeftxAxis(), DS4.GetLeftyAxis(), DS4.GetRightxAxis());
  }
}

void gyro_power() {
  Serial.print(turn_power);  Serial.print("\t");
}
