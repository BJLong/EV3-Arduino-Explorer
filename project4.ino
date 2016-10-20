#include <EVs_UIModule.h>
#include <SPI.h>
#include <EVShield.h>
#include <EVs_EV3Ultrasonic.h>
#include <Wire.h>

EVShield evs(0x34,0x36);
EVs_EV3Ultrasonic us;
EVs_UIModule uim = EVs_UIModule(7,8,9);

void setup() {
  // put your setup code here, to run once:
  char str[200];
  evs.init(SH_HardwareI2C);
  us.init(&evs,SH_BAS1);
  evs.bank_a.motorReset();
  evs.bank_b.motorReset();
  // second parameter is port, YMMV
  us.setMode(MODE_Sonar_CM);
  uim.begin();
  for(int i = 0; i < 100; i++){
    evs.ledSetRGB(i,100-i,0);
    delay(20);
  }
  sprintf (str, "Press GO to continue");
  uim.writeLine(1, 1, str, 1, 555555);
  evs.waitForButtonPress(BTN_GO);
  uim.clearScreen();

//  evs.bank_a.motorRunDegrees(SH_Motor_1, SH_Direction_Forward, SH_Speed_Slow, 90, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);
//  evs.bank_a.motorRunDegrees(SH_Motor_1, SH_Direction_Forward, SH_Speed_Slow, 90, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);
//  evs.bank_a.motorRunDegrees(SH_Motor_1, SH_Direction_Reverse, SH_Speed_Slow, 270, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);
//  evs.bank_a.motorRunDegrees(SH_Motor_1, SH_Direction_Reverse, SH_Speed_Slow, 90, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);

//  evshield.bank_a.motorRunRotations(SH_Motor_1, 
//                     SH_Direction_Reverse, 
//                     SH_Speed_Medium,
//                     2, 
//                     SH_Completion_Wait_For,
//                     SH_Next_Action_BrakeHold);
//    
//    delay(1000);
//    Serial.println("Bank A motors >>");
//    sprintf(str, "Run away");
//    Serial.println(str);
//    str[0] = '\0';
//    evshield.bank_a.motorRunUnlimited(SH_Motor_Both, 
//                     SH_Direction_Reverse, 
//                     SH_Speed_Medium);
}

void loop() {
//  put your main code here, to run repeatedly:
  int value[7];
  while(value[3] > 10){
    value[3] = us.getDist();
    evs.bank_b.motorRunUnlimited(SH_Motor_Both, 
                       SH_Direction_Forward, 
                       SH_Speed_Medium);
  }
  evs.bank_b.motorStop(SH_Motor_Both, SH_Next_Action_BrakeHold);
  
  evs.bank_a.motorRunDegrees(SH_Motor_1, SH_Direction_Forward, 30, 210, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);
  value[0] = us.getDist();
  delay(100);
  evs.bank_a.motorRunDegrees(SH_Motor_1, SH_Direction_Reverse, 30, 70, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);
  value[1] = us.getDist();
  delay(100);
  evs.bank_a.motorRunDegrees(SH_Motor_1, SH_Direction_Reverse, 30, 70, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);
  value[2] = us.getDist();
  delay(100);
  evs.bank_a.motorRunDegrees(SH_Motor_1, SH_Direction_Reverse, 30, 70, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);
  value[3] = us.getDist();
  delay(100);
  evs.bank_a.motorRunDegrees(SH_Motor_1, SH_Direction_Reverse, 30, 70, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);
  value[4] = us.getDist();
  delay(100);
  evs.bank_a.motorRunDegrees(SH_Motor_1, SH_Direction_Reverse, 30, 70, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);
  value[5] = us.getDist();
  delay(100);
  evs.bank_a.motorRunDegrees(SH_Motor_1, SH_Direction_Reverse, 30, 70, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);
  value[6] = us.getDist();
  delay(100);
  //evs.bank_a.motorRunDegrees(SH_Motor_1, SH_Direction_Forward, 30, 210, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);
  //evs.bank_a.motorRunTachometer(SH_Motor_1,SH_Direction_Reverse, 20, 0, SH_Move_Absolute, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);
  evs.bank_a.motorRunTachometer(SH_Motor_1,SH_Direction_Forward, 20, 0, SH_Move_Absolute, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);
  delay(100);
  
  int max = 3;
  for(int i = 0; i < 8; i++){
    if(value[i] > value[max] && value[i] < 150){
      max = i;
    }
  }
  evs.bank_b.motorStop(SH_Motor_Both, SH_Next_Action_BrakeHold);
  if(max == 0){
    evs.bank_b.motorRunDegrees(SH_Motor_1, SH_Direction_Reverse, 30, 810, SH_Completion_Dont_Wait, SH_Next_Action_BrakeHold);
    evs.bank_b.motorRunDegrees(SH_Motor_2, SH_Direction_Forward, 30, 810, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);
  }else if(max == 1){
    evs.bank_b.motorRunDegrees(SH_Motor_1, SH_Direction_Reverse, 30, 540, SH_Completion_Dont_Wait, SH_Next_Action_BrakeHold);
    evs.bank_b.motorRunDegrees(SH_Motor_2, SH_Direction_Forward, 30, 540, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);
  }else if(max == 2){
    evs.bank_b.motorRunDegrees(SH_Motor_1, SH_Direction_Reverse, 30, 270, SH_Completion_Dont_Wait, SH_Next_Action_BrakeHold);
    evs.bank_b.motorRunDegrees(SH_Motor_2, SH_Direction_Forward, 30, 270, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);
  }else if(max == 3){
    evs.bank_b.motorRunDegrees(SH_Motor_1, SH_Direction_Reverse, 30, 360, SH_Completion_Dont_Wait, SH_Next_Action_BrakeHold);
    evs.bank_b.motorRunDegrees(SH_Motor_2, SH_Direction_Reverse, 30, 360, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);
    evs.bank_b.motorRunDegrees(SH_Motor_1, SH_Direction_Reverse, 30, 1400, SH_Completion_Dont_Wait, SH_Next_Action_BrakeHold);
    evs.bank_b.motorRunDegrees(SH_Motor_2, SH_Direction_Forward, 30, 1400, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);
  }else if(max == 4){
    evs.bank_b.motorRunDegrees(SH_Motor_1, SH_Direction_Forward, 30, 270, SH_Completion_Dont_Wait, SH_Next_Action_BrakeHold);
    evs.bank_b.motorRunDegrees(SH_Motor_2, SH_Direction_Reverse, 30, 270, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);
  }else if(max == 5){
    evs.bank_b.motorRunDegrees(SH_Motor_1, SH_Direction_Forward, 30, 540, SH_Completion_Dont_Wait, SH_Next_Action_BrakeHold);
    evs.bank_b.motorRunDegrees(SH_Motor_2, SH_Direction_Reverse, 30, 540, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);
  }else if(max == 6){
    evs.bank_b.motorRunDegrees(SH_Motor_1, SH_Direction_Forward, 30, 810, SH_Completion_Dont_Wait, SH_Next_Action_BrakeHold);
    evs.bank_b.motorRunDegrees(SH_Motor_2, SH_Direction_Reverse, 30, 810, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);
  }
  
  evs.bank_b.motorStop(SH_Motor_Both, SH_Next_Action_BrakeHold);
//  char str[200];
  
//  sprintf (str, "Distance: %d cm", value);
//  uim.writeLine(1, 1, str, 1, 555555);
  

}
