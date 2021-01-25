#include<arduino.h>
void OutPut_Motor(int a, int b, int p, int Motor_power_OutPut) {
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(p, OUTPUT);

  if (Motor_power_OutPut == 0) {
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    analogWrite(p, 0);
  }
  if (Motor_power_OutPut > 0) {
    digitalWrite(a, HIGH);
    digitalWrite(b, LOW);
    analogWrite(p, Motor_power_OutPut);
  }
  if (Motor_power_OutPut < 0) {
    digitalWrite(a, LOW);
    digitalWrite(b, HIGH);
    analogWrite(p, abs(Motor_power_OutPut));
  }

}
