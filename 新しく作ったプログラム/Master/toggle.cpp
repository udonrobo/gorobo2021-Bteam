#include<arduino.h>
byte countR1;
byte countR2;
byte count_batu;
byte countL2;
byte countL1;
byte count_sankaku;
byte count_sikaku;
byte count_maru;

byte toggle_R1_back;
byte toggle_R2_back;
byte toggle_batu_back;
byte toggle_batu_cal;
byte toggle_L2_back;
byte toggle_L1_back;
byte toggle_sankaku_back;
byte toggle_sikaku_back;
byte click_maru_back;

void toggle_R1(byte INPUT_R1) {
  if  (INPUT_R1 == 1) {
    if (countR1 == 0) {
      toggle_R1_back++;
      if (toggle_R1_back >= 2) {
        toggle_R1_back = 0;
      }
      countR1 = 1;
    }
  } else {
    countR1 = 0;
  }
}

void toggle_R2(byte INPUT_R2) {
  if  (INPUT_R2 == 1) {
    if (countR2 == 0) {
      toggle_R2_back++;
      if (toggle_R2_back >= 2) {
        toggle_R2_back = 0;
      }
      countR2 = 1;
    }
  } else {
    countR2 = 0;
  }
}

void toggle_batu(byte INPUT_batu) {
  if  (INPUT_batu == 1) {
    if (count_batu == 0) {
      toggle_batu_cal++;
      if (toggle_batu_cal >= 2) {
        toggle_batu_cal = 0;
      }
      count_batu = 1;
    }
  } else {
    count_batu = 0;
  }
  if (toggle_batu_cal == 0) {
    toggle_batu_back = 1;
  } else {
    toggle_batu_back = 0;
  }
}

void toggle_L2(byte INPUT_L2) {
  if  (INPUT_L2 == 1) {
    if (countL2 == 0) {
      toggle_L2_back++;
      if (toggle_L2_back >= 2) {
        toggle_L2_back = 0;
      }
      countL2 = 1;
    }
  } else {
    countL2 = 0;
  }
}
void toggle_L1(byte INPUT_L1) {
  if  (INPUT_L1 == 1) {
    if (countL1 == 0) {
      toggle_L1_back++;
      if (toggle_L1_back >= 2) {
        toggle_L1_back = 0;
      }
      countL1 = 1;
    }
  } else {
    countL1 = 0;
  }
}
void toggle_sankaku(byte INPUT_sankaku) {
  if  (INPUT_sankaku == 1) {
    if (count_sankaku == 0) {
      toggle_sankaku_back++;
      if (toggle_sankaku_back >= 2) {
        toggle_sankaku_back = 0;
      }
      count_sankaku = 1;
    }
  } else {
    count_sankaku = 0;
  }
}
void toggle_sikaku(byte INPUT_sikaku) {
  if  (INPUT_sikaku == 1) {
    if (count_sikaku == 0) {
      toggle_sikaku_back++;
      if (toggle_sikaku_back >= 2) {
        toggle_sikaku_back = 0;
      }
      count_sikaku = 1;
    }
  } else {
    count_sikaku = 0;
  }
}
void click_maru(byte INPUT_maru) {
  if (INPUT_maru == 1) {
    if (count_maru == 0) {
      click_maru_back = 1;
      count_maru = 1;
    } else {
      click_maru_back = 0;
    }
  } else {
    click_maru_back = 0;
    count_maru = 0;
  }
}

byte toggle_Send_R1() {
  return toggle_R1_back;
}
byte toggle_Send_R2() {
  return toggle_R2_back;
}
byte toggle_Send_L2() {
  return toggle_L2_back;
}
byte toggle_Send_batu() {
  return toggle_batu_back;
}
byte toggle_Send_L1() {
  return  toggle_L1_back;
}
byte toggle_Send_sankaku() {
  return toggle_sankaku_back;
}
byte toggle_Send_sikaku() {
  return toggle_sikaku_back;
}
byte click_Send_maru() {
  return click_maru_back;
}
