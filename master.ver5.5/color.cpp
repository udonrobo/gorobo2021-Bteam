#include "Controller.h"
#include "MasterWriter.h"
#include "submaster.h"

void ps_blue() {
  ps_LED.SetSingleData(2, 0);
  ps_LED.SetSingleData(3, 0);
  ps_LED.SetSingleData(4, 200);
}

void ps_red() {
  ps_LED.SetSingleData(2, 200);
  ps_LED.SetSingleData(3, 0);
  ps_LED.SetSingleData(4, 0);
}

void ps_pink() {
  ps_LED.SetSingleData(2, 200);
  ps_LED.SetSingleData(3, 0);
  ps_LED.SetSingleData(4, 200);
}

void ps_yellow() {
  ps_LED.SetSingleData(2, 200);
  ps_LED.SetSingleData(3, 200);
  ps_LED.SetSingleData(4, 0);
}

void tape_colorfull(){
  tape_LED.SetSingleData(2,200);
  tape_LED.SetSingleData(3,200);
  tape_LED.SetSingleData(4,200);
}

void tape_red(){
  tape_LED.SetSingleData(2,200);
  tape_LED.SetSingleData(3,0);
  tape_LED.SetSingleData(4,0);  
}
