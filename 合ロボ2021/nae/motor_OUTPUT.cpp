#include<arduino.h>
void motor_OUTPUT(byte a, byte b, byte p, byte Motor_power, byte Motor_muki) {
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(p, OUTPUT);

  if (Motor_power == 0) {
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    analogWrite(p, 0);
  } else if (Motor_muki == 0) {
    digitalWrite(a, HIGH);
    digitalWrite(b, LOW);
    analogWrite(p, Motor_power);
  } else {
    digitalWrite(a, LOW);
    digitalWrite(b, HIGH);
    analogWrite(p, Motor_power);
  }
}
