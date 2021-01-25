#include<arduino.h>
#include<Wire.h>

void Slave_Send_omuni(byte Motor_power_omuni1, byte Motor_power_omuni2, byte Motor_power_omuni3, byte Motor_power_omuni4, byte Motor_power_omuni_muki) {
  Wire.beginTransmission(3);
  Wire.write(Motor_power_omuni1);
  Wire.write(Motor_power_omuni2);
  Wire.write(Motor_power_omuni3);
  Wire.write(Motor_power_omuni4);
  Wire.write(Motor_power_omuni_muki);
}

void Slave_Send_syoukou(byte Motor_power_syoukou, byte Motor_muki_syoukou) {
  Wire.beginTransmission(5);
  Wire.write(Motor_power_syoukou);
  Wire.write(Motor_muki_syoukou);
}

void Slave_Send_dansa(byte Motor_power_air) {
  Wire.beginTransmission(7);
  Wire.write(Motor_power_air);
}

void Slave_Send_hanakaisyuu(byte hanakaisyuu_Servo) {
  Wire.beginTransmission(8);
  Wire.write(hanakaisyuu_Servo);
}

void Slave_Send_nae(byte Motor_power1,byte Motor_power2,byte Motor_power3,byte Motor_muki) {
  Wire.beginTransmission(4);
  Wire.write(Motor_power1);
  Wire.write(Motor_power2);
  Wire.write(Motor_power3);
  Wire.write(Motor_muki);
}

void Slave_Send_hassya(byte hassya_sorenoid) {
  Wire.beginTransmission(1);
  Wire.write(hassya_sorenoid);
}
