#pragma once
#include <arduino.h>
#include <Wire.h>


class IM920 {
  private:
    bool song;
    bool oldData[5];
    bool newData[5];
    bool click_Data[5];
    bool Toggle_Data[5];
    bool redSwitch, greenSwitch, botton1, botton2, playing;
    uint16_t waitTime = 0;
    bool* Play;
    uint8_t* save[2];
    uint16_t index = 0;

    uint8_t count   = 0;
    uint8_t count4  = 0;
    uint8_t count8  = 0;
    uint8_t count16 = 0;
    uint8_t count32 = 0;
    uint8_t OldData[5];
    uint8_t NewData[5];
    bool Click_Data[5];

  public:

    IM920(uint16_t waittime = 1000) { //ループ周期は10ms
      if (waittime < 10)waittime = 10;
      waitTime = waittime / 10;
      save[0] = new uint8_t [waitTime];
      save[1] = new uint8_t [waitTime];
      Play    = new bool [waitTime];
      for (int i = 0; i < waitTime; i++) {
        save[0][i] = 0;
        save[1][i] = 0;
        Play[i] = 0;
      }
    }

    //    virtual ~IM920() {
    //      delete[] save[0];
    //      delete[] save[1];
    //      delete[] Play;
    //    }

    void Update() {
      Wire.requestFrom(6, 3);
      uint8_t buf[3];
      while (Wire.available()) {
        buf[0] = Wire.read();
        buf[1] = Wire.read();
        buf[2] = Wire.read();
      }

      redSwitch    = bitRead(buf[0], 0);
      greenSwitch  = bitRead(buf[0], 1);
      botton1      = bitRead(buf[0], 2);
      botton2      = bitRead(buf[0], 3);
      song         = bitRead(buf[0], 5);

      playing      = Play[index];//遅延
      count        = save[0][index];
      count32      = save[1][index];

      Play[index]      = bitRead(buf[0], 4);
      save[0][index]   = buf[1];
      save[1][index++] = buf[2] - 1;//0-15

      if (index >= waitTime)
        index = 0;

      count4  = count32 / 8;
      count8  = count32 / 4;
      count16 = count32 / 2;
      count4++;
      count8++;
      count16++;
      count32++;

      newData[0] = redSwitch;
      newData[1] = greenSwitch;
      newData[2] = botton1;
      newData[3] = botton2;
      newData[4] = playing;

      NewData[0] = count;
      NewData[1] = count4;
      NewData[2] = count8;
      NewData[3] = count16;
      NewData[4] = count32;

      for (int i = 0; i < 5; i++) {
        if (oldData[i] == 0 && newData[i] == 1)
          click_Data[i] = true;
        else
          click_Data[i] = false;
        oldData[i] = newData[i];

        if (click_Data[i])   Toggle_Data[i] ^= 1;
      }

      if (OldData[0] < NewData[0])
        Click_Data[0] = true;
      else
        Click_Data[0] = false;
      OldData[0] = NewData[0];

      for (int i = 1; i < 5; i++) {
        if (OldData[i] < NewData[i] || Click_Data[0] || click_Data[4]) //値が大きくなった時と小節が繰り上がった時
          Click_Data[i] = true;
        else
          Click_Data[i] = false;
        OldData[i] = NewData[i];
      }
    }

    bool getSong() {
      return song;
    }
    bool GetRedSwitch() {
      return redSwitch;
    }
    bool GetGreenSwitch() {
      return greenSwitch;
    }
    bool GetBotton1() {
      return botton1;
    }
    bool GetBotton2() {
      return botton2;
    }

    bool GetRedSwitchClick() {
      return click_Data[0];
    }
    bool GetGreenSwitchClick() {
      return click_Data[1];
    }
    bool GetBotton1Click() {
      return click_Data[2];
    }
    bool GetBotton2Click() {
      return click_Data[3];
    }

    bool GetRedSwitchToggle() {
      return Toggle_Data[0];
    }
    bool GetGreenSwitchToggle() {
      return Toggle_Data[1];
    }
    bool GetBotton1Toggle() {
      return Toggle_Data[2];
    }
    bool GetBotton2Toggle() {
      return Toggle_Data[3];
    }

    bool GetPlaying() {
      return playing;
    }
    uint8_t GetbarCount() {
      return playing ? count : 0;
    }
    uint8_t quarter() {
      return count4;
    }
    uint8_t eighth() {
      return count8;
    }
    uint8_t sixteenth() {
      return count16;
    }
    uint8_t thirtysecond() {
      return count32;
    }

    bool GetCountClick() {
      return Click_Data[0];
    }
    bool quarterClick() {
      return Click_Data[1];
    }
    bool eighthClick() {
      return Click_Data[2];
    }
    bool sixteenthClick() {
      return Click_Data[3];
    }
    bool thirtysecondClick() {
      return Click_Data[4];
    }

};
extern IM920 im920;
