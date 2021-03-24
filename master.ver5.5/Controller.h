#pragma once

#include <Wire.h>
#include "arduino.h"

constexpr int16_t CutAnalogValue = 20;  // アナログスティックの中間不感値
constexpr int16_t CutValue = CutAnalogValue * 2;


class ControllerManager {

  private:

    struct buttonData {
      bool oldData = 0;
      bool newData = 0;
    };

    bool Select, L3, R3, START, PS, Up, Right, Down, Left;
    bool L2, R2, L1, R1, Triangle, Circle, Cross, Square;
    bool Touch;

    int16_t LeftHatX, LeftHatY;
    int16_t RightHatX, RightHatY;
    int16_t AnalogL2, AnalogR2;

    int16_t RightHatX_map, RightHatY_map;
    int16_t LeftHatX_map, LeftHatY_map;

    int16_t right_theta, theta;
    uint16_t r, right_r;
    int16_t LeftxAxis, LeftyAxis, RightxAxis, RightyAxis;

    buttonData buttonStock[17];
    bool Click_Data[17] = {};
    bool Toggle_Data[17] = {};

    bool RightHatX_RE, LeftHatX_RE, RightHatY_RE, LeftHatY_RE; //Rising Edge
    bool RightHatX_FE, LeftHatX_FE, RightHatY_FE, LeftHatY_FE; //Falling Edge

    double turn_param = 0.6;

    int CountUp_Data[17] = {};

    const int I2C_Address;

  public:

    ControllerManager(int Address) : I2C_Address(Address) {}

    void Update() {
      Wire.requestFrom(I2C_Address, 9);
      uint8_t buf[] = { 0, 0, 127, 127, 127, 127, 0, 0, 0};
      while (Wire.available()) {
        buf[0] = Wire.read();
        buf[1] = Wire.read();
        buf[2] = Wire.read();
        buf[3] = Wire.read();
        buf[4] = Wire.read();
        buf[5] = Wire.read();
        buf[6] = Wire.read();
        buf[7] = Wire.read();
        buf[8] = Wire.read();
      }
      Select = bitRead(buf[0], 0);
      L3 = bitRead(buf[0], 1);
      R3 = bitRead(buf[0], 2);
      START = bitRead(buf[0], 3);
      Up = bitRead(buf[0], 4);
      Right = bitRead(buf[0], 5);
      Down = bitRead(buf[0], 6);
      Left = bitRead(buf[0], 7);

      L2 = bitRead(buf[1], 0);
      R2 = bitRead(buf[1], 1);
      L1 = bitRead(buf[1], 2);
      R1 = bitRead(buf[1], 3);
      Triangle = bitRead(buf[1], 4);
      Circle = bitRead(buf[1], 5);
      Cross = bitRead(buf[1], 6);
      Square = bitRead(buf[1], 7);

      PS = bitRead(buf[8], 0);
      Touch = bitRead(buf[8], 1);
      //Touch = 0;

      buttonStock[0].newData = Triangle;
      buttonStock[1].newData = Circle;
      buttonStock[2].newData = Cross;
      buttonStock[3].newData = Square;

      buttonStock[4].newData = Up;
      buttonStock[5].newData = Right;
      buttonStock[6].newData = Down;
      buttonStock[7].newData = Left;

      buttonStock[8].newData = START;
      buttonStock[9].newData = Select;

      buttonStock[10].newData = Touch;

      buttonStock[11].newData = L2;
      buttonStock[12].newData = R2;
      buttonStock[13].newData = L1;
      buttonStock[14].newData = R1;
      buttonStock[15].newData = L3;
      buttonStock[16].newData = R3;

      for (int i = 0; i < 17; i++) {
        if (buttonStock[i].oldData == 0 && buttonStock[i].newData == 1) {
          Click_Data[i] = true;
        }
        else
          Click_Data[i] = false;

        buttonStock[i].oldData = buttonStock[i].newData;
      }

      for (int i = 0; i < 17; i++)
        if (Click_Data[i])   Toggle_Data[i] ^= 1;

      for (int i = 0; i < 17; i++)
        if (Click_Data[i])       CountUp_Data[i]++;

      if (PS) {
        for (int i = 0; i < 17; i++) {
          CountUp_Data[i] = 0;
        }
      }

      if (abs(127 - buf[2]) < CutAnalogValue)
        buf[2] = 127;
      else if (127 - buf[2] < 0)
        buf[2] = map(buf[2], 127 + CutAnalogValue , 255, 127, 255);
      else
        buf[2] = map(buf[2], 127 - CutAnalogValue , 0, 127, 0);

      if (abs(127 - buf[3]) < CutAnalogValue)
        buf[3] = 127;
      else if (127 - buf[3] < 0)
        buf[3] = map(buf[3], 127 + CutAnalogValue , 255, 127, 255);
      else
        buf[3] = map(buf[3], 127 - CutAnalogValue , 0, 127, 0);

      if (abs(127 - buf[4]) < CutAnalogValue)
        buf[4] = 127;
      else if (127 - buf[4] < 0)
        buf[4] = map(buf[4], 127 + CutAnalogValue , 255, 127, 255);
      else
        buf[4] = map(buf[4], 127 - CutAnalogValue , 0, 127, 0);

      if (abs(127 - buf[5]) < CutAnalogValue)
        buf[5] = 127;
      else if (127 - buf[5] < 0)
        buf[5] = map(buf[5], 127 + CutAnalogValue , 255, 127, 255);
      else
        buf[5] = map(buf[5], 127 - CutAnalogValue , 0, 127, 0);

      RightHatX = buf[2];
      RightHatY = buf[3];
      LeftHatX = buf[4];
      LeftHatY = buf[5];

      AnalogL2 = buf[6];
      AnalogR2 = buf[7];

      RightHatX_map = buf[2] - 127;
      RightHatY_map = -(buf[3] - 127);
      LeftHatX_map = buf[4] - 127;
      LeftHatY_map = -(buf[5] - 127);

      r = sqrt((LeftHatX_map * LeftHatX_map) + (LeftHatY_map * LeftHatY_map)) * 2;
      r = constrain(r, 0, 255);
      right_r = sqrt((RightHatX_map * RightHatX_map) + (RightHatY_map * RightHatY_map)) * 2;
      right_r = constrain(right_r, 0, 255);

      float left_Rad = atan2(LeftHatY_map, LeftHatX_map);
      theta = round(degrees(left_Rad));
      if (theta < 0) theta += 360;
      if (theta > 359) theta -= 360;

      float right_Rad = atan2(RightHatY_map, RightHatX_map);
      right_theta = round(degrees(right_Rad));
      if (right_theta < 0) right_theta += 360;
      if (right_theta > 359) right_theta -= 360;

      LeftxAxis = r * cos(radians((float)theta));
      LeftyAxis = r * sin(radians((float)theta));
      RightxAxis = right_r * cos(radians((float)right_theta));
      RightyAxis = right_r * sin(radians((float)right_theta));
    }

    bool GetTouch() {
      return Touch;
    }
    bool GetPS() {
      return PS;
    }
    bool GetStart() {
      return START;
    }
    bool GetSelect() {
      return Select;
    }
    bool GetL3() {
      return L3;
    }
    bool GetR3() {
      return R3;
    }
    bool GetUp() {
      return Up;
    }
    bool GetRight() {
      return Right;
    }
    bool GetDown() {
      return Down;
    }
    bool GetLeft() {
      return Left;
    }
    bool GetL2() {
      return L2;
    }
    bool GetR2() {
      return R2;
    }
    bool GetL1() {
      return L1;
    }
    bool GetR1() {
      return R1;
    }
    bool GetTriangle() {
      return Triangle;
    }
    bool GetCircle() {
      return Circle;
    }
    bool GetCross() {
      return Cross;
    }
    bool GetSquare() {
      return Square;
    }
    /* Click */
    bool GetTriangleClick() {
      return Click_Data[0];
    }
    bool GetCircleClick() {
      return Click_Data[1];
    }
    bool GetCrossClick() {
      return Click_Data[2];
    }
    bool GetSquareClick() {
      return Click_Data[3];
    }

    bool GetUpClick() {
      return Click_Data[4];
    }
    bool GetRightClick() {
      return Click_Data[5];
    }
    bool GetDownClick() {
      return Click_Data[6];
    }
    bool GetLeftClick() {
      return Click_Data[7];
    }

    bool GetStartClick() {
      return Click_Data[8];
    }
    bool GetShareClick() {
      return Click_Data[9];
    }
    bool GetTouchClick() {
      return Click_Data[10];
    }

    bool GetL2Click() {
      return Click_Data[11];
    }
    bool GetR2Click() {
      return Click_Data[12];
    }
    bool GetL1Click() {
      return Click_Data[13];
    }
    bool GetR1Click() {
      return Click_Data[14];
    }
    bool GetL3Click() {
      return Click_Data[15];
    }
    bool GetR3Click() {
      return Click_Data[16];
    }

    /*    Toggle    */
    bool GetTriangleToggle() {
      return Toggle_Data[0];
    }
    bool GetCircleToggle() {
      return Toggle_Data[1];
    }
    bool GetCrossToggle() {
      return Toggle_Data[2];
    }
    bool GetSquareToggle() {
      return Toggle_Data[3];
    }

    bool GetUpToggle() {
      return Toggle_Data[4];
    }
    bool GetRightToggle() {
      return Toggle_Data[5];
    }
    bool GetDownToggle() {
      return Toggle_Data[6];
    }
    bool GetLeftToggle() {
      return Toggle_Data[7];
    }

    bool GetStartToggle() {
      return Toggle_Data[8];
    }
    bool GetShareToggle() {
      return Toggle_Data[9];
    }
    bool GetTouchToggle() {
      return Toggle_Data[10];
    }

    bool GetL2Toggle() {
      return Toggle_Data[11];
    }
    bool GetR2Toggle() {
      return Toggle_Data[12];
    }
    bool GetL1Toggle() {
      return Toggle_Data[13];
    }
    bool GetR1Toggle() {
      return Toggle_Data[14];
    }
    bool GetL3Toggle() {
      return Toggle_Data[15];
    }
    bool GetR3Toggle() {
      return Toggle_Data[16];
    }

    /*      CountUp     */
    int GetTriangleCountUp() {
      return CountUp_Data[0];
    }
    int GetCircleCountUp() {
      return CountUp_Data[1];
    }
    int GetCrossCountUp() {
      return CountUp_Data[2];
    }
    int GetSquareCountUp() {
      return CountUp_Data[3];
    }

    int GetUpCountUp() {
      return CountUp_Data[4];
    }
    int GetRightCountUp() {
      return CountUp_Data[5];
    }
    int GetDownCountUp() {
      return CountUp_Data[6];
    }
    int GetLeftCountUp() {
      return CountUp_Data[7];
    }

    int GetStartCountUp() {
      return CountUp_Data[8];
    }
    int GetShareCountUp() {
      return CountUp_Data[9];
    }
    int GetTouchCountUp() {
      return CountUp_Data[10];
    }

    int GetL2CountUp() {
      return CountUp_Data[11];
    }
    int GetR2CountUp() {
      return CountUp_Data[12];
    }
    int GetL1CountUp() {
      return CountUp_Data[13];
    }
    int GetR1CountUp() {
      return CountUp_Data[14];
    }
    int GetL3CountUp() {
      return CountUp_Data[15];
    }
    int GetR3CountUp() {
      return CountUp_Data[16];
    }

    int16_t GetLeftHatX() {
      return LeftHatX;
    }
    int16_t GetLeftHatY() {
      return LeftHatY;
    }
    int16_t GetRightHatX() {
      return RightHatX;
    }
    int16_t GetRightHatY() {
      return RightHatY;
    }
    int16_t GetAnalogL2() {
      return AnalogL2;
    }
    int16_t GetAnalogR2() {
      return AnalogR2;
    }

    int16_t Gettheta() {
      return theta;
    }
    uint16_t Getr() {
      return r;
    }
    int16_t GetLeftxAxis() {
      return LeftxAxis;
    }
    int16_t GetLeftyAxis() {
      return LeftyAxis;
    }
    int16_t GetRightxAxis() {
      return RightxAxis;
    }
    int16_t GetRightyAxis() {
      return RightyAxis;
    }
};

extern ControllerManager DS4;
