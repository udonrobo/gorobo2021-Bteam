#include<arduino.h>

void Motor_OUTPUT(int a, int b, int p, int motor_power) {
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);

  if (motor_power == 0) {
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    analogWrite(p, 0);
  }
  if (motor_power > 0) {
    digitalWrite(a, HIGH);
    digitalWrite(b, LOW);
    analogWrite(p, motor_power);
  }
  if (motor_power < 0) {
    digitalWrite(a, LOW);
    digitalWrite(b, HIGH);
    analogWrite(p, abs(motor_power));
  }
}
