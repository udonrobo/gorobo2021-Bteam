#pragma once
#include <arduino.h>
#include <Wire.h>

class MasterReader {
  private:
    int size;
    int address;
    byte* data;
  public:
    MasterReader(int Address, int Size) {
      data = new byte[Size];
      for (int i = 0; i < Size; i++)
        data[i] = 0;
      address = Address;
      size = Size;
    }

    void Update() {
      Wire.requestFrom(address, size);
      while (Wire.available()) {
        for (int i = 0; i < size; i++)
          data[i] = Wire.read();
      }
    }

    byte GetData(int array_num) {
      return data[array_num - 1];
    }

    bool GetBitData(int array_num, int bit_num) {
      return bitRead(data[array_num - 1], bit_num);
    }

    void read_show() {
      for (int i = 0; i < size; i++) {
        Serial.print(data[i]);
        Serial.print("\t");
      }
    }
};

extern MasterReader LimitSw, InterFace;
