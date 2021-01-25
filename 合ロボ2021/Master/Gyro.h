#pragma once
#include <arduino.h>

class Gyro {
  private:

    double offset;
    bool Serialflag;

    double gyro_now;    //gyroの現在値
    double Gyro_offset; //gyroのoffserの値
    double gyro_bef;    //10ms前のgyroの値
    double gyro_delta ; //10ms間のgyroの値
    double gyro_cal;   //gyroの計算値
    double true_yaw = 0;
    double enc_shoukou_gyro;
    double Alltime_gyro;
    float i = 0;

  public:

    // 生の値を得る(なべし製) //
    double GetGyro() {
      int16_t yaw = 0;

      //      static float i = 0;
      if (Serial.available() >= 3) {
        Serialflag = true;
        if (Serial.read() == 'H') {
          yaw = (Serial.read() << 8) | Serial.read();
          true_yaw = (double)yaw / 100;
          true_yaw -= offset;
          if (true_yaw > 180)
            true_yaw -= 360;
          else if (true_yaw < -180)
            true_yaw += 360;
          i = true_yaw;
          return true_yaw;
        }
      }
      return i;
    }

    //  GyroのOffset //
    void OffSet_Update() {
      Gyro_offset = GetGyro();
      gyro_cal = gyro_now;
    }

    void First_Gyro() {
      enc_shoukou_gyro = GetGyro();
    }

    // Gyroの現在の値を計算 //
    void GyroCaluculate() {
      gyro_now = GetGyro() - Gyro_offset;
      Alltime_gyro = GetGyro() - enc_shoukou_gyro;

      if (gyro_now > 179)
        gyro_now -= 359;
      else if (gyro_now < -179)
        gyro_now += 359;

      if (Alltime_gyro > 179)
        Alltime_gyro -= 359;
      else if (Alltime_gyro < -179)
        Alltime_gyro += 359;

      gyro_cal += gyro_delta;

      if ((gyro_bef >= 90) && ((0 > gyro_now) && (gyro_now >= -179)))
        gyro_bef -= 359;
      else if ((gyro_bef <= -90) && ((0 < gyro_now) && (gyro_now <= 179)))
        gyro_bef += 359;

      gyro_delta = gyro_now - gyro_bef;
      gyro_bef = gyro_now;
    }

    double yaw() {
      return gyro_now;
    }

    double Angle() {
      return Alltime_gyro;
    }

    // 計算値を返す //
    double Gyro_deg() {
      return gyro_cal;
    }

    double Gyro_rad() {
      return (PI / 180) * gyro_cal;
    }

    void gyro_show() {
      Serial.print(GetGyro());     Serial.print("\t");
      Serial.print(Gyro_offset);  Serial.print("\t");
      Serial.print(gyro_now);     Serial.print("\t");
      //      Serial.print(i);  Serial.print("t");
      //      Serial.print(gyro_bef);     Serial.print("\t");
      Serial.print(gyro_cal);     Serial.print("\t");
      Serial.print(Alltime_gyro); Serial.print("\t");
      //      Serial.print(Gyro_rad());   Serial.print("\t");
      //      Serial.print (Gyro_rad()); Serial.print("\t");
    }
};

extern Gyro gyro;
