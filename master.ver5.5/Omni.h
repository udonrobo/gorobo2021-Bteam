#include <arduino.h>
#pragma once

class Omni {
  private:
    int MaxPower;
    int turn_max;
    int16_t Power[4];

  public:
    Omni(int max_power, int max_turn) {
      MaxPower = max_power;
      turn_max = max_turn;
    }


    void move(int16_t x, int16_t y, int16_t turn) {
      //各モータの強さの計算
      Power[0] = x - y + turn;  //右前のモータ
      Power[1] = x + y + turn;  //左前のモータ
      Power[2] = -x + y + turn;  //左後ろのモータ
      Power[3] = -x - y + turn;  //右後ろのモータ

      //一番大きい値の取得
      int16_t max_ = max(max(abs(Power[0]), abs(Power[1])), max(abs(Power[2]), abs(Power[3])));

      if (max_ > MaxPower) {
        float amp = float(MaxPower) / max_;
        Power[0] = int16_t(Power[0] * amp);
        Power[1] = int16_t(Power[1] * amp);
        Power[2] = int16_t(Power[2] * amp);
        Power[3] = int16_t(Power[3] * amp);
      }

      if (turn > turn_max) {
        float amp_t = float(turn_max) / turn;
        Power[0] = int16_t(Power[0] * amp_t);
        Power[1] = int16_t(Power[1] * amp_t);
        Power[2] = int16_t(Power[2] * amp_t);
        Power[3] = int16_t(Power[3] * amp_t);
      }
    }

    void SetMaxPwm(int MaxPower) {
      this->MaxPower = MaxPower;
    }
    int16_t motorFR() {
      return Power[0];
    }

    int16_t motorFL() {
      return Power[1];
    }

    int16_t motorBL() {
      return Power[2];
    }

    int16_t motorBR() {
      return Power[3];
    }
};


extern Omni omni;
