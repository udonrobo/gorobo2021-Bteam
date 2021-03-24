#pragma once
#include<arduino.h>

class motor {
  private:
    int pin_a, pin_b, pin_p;
    double motor_power;

  public:
    motor(int pin_A, int pin_B, int pin_P) : pin_a(pin_A), pin_b(pin_B), pin_p(pin_P) {
      pinMode(pin_A, OUTPUT);
      pinMode(pin_B, OUTPUT);
    }

    void motor_move(double motor_data) {
      motor_power = motor_data;

      if (motor_power > 0) {
        digitalWrite(pin_a, HIGH);
        digitalWrite(pin_b, LOW);
        analogWrite(pin_p, motor_data);
      }
      else if (motor_power < 0) {
        digitalWrite(pin_a, LOW);
        digitalWrite(pin_b, HIGH);
        analogWrite(pin_p, abs(motor_data));
      }
      else if (motor_power == 0) {
        digitalWrite(pin_a, HIGH);
        digitalWrite(pin_b, HIGH);
        analogWrite(pin_p, 0);
      }
    }

    void show_motor() {
      Serial.print(motor_power); Serial.print("\t");
    }
};
