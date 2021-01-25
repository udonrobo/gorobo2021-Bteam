#include<arduino.h>


void output(int Motor_Speed, int air_front, int air_back) {
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);

  digitalWrite(8, HIGH);
  digitalWrite(10, LOW);
  analogWrite(9, Motor_Speed);

  digitalWrite(11, HIGH);
  digitalWrite(13, LOW);
  analogWrite(12, Motor_Speed);

digitalWrite(5,air_front);
digitalWrite(6,air_back);

}
