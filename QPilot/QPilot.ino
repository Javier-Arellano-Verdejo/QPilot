//////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  QPilot
//
//             Author: J. Arellano-Verdejo (J@Vo)
//         Created on: February 26, 2015
//  Last modification: April 10, 2015
//            Version: 0.1
//
//////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Wire.h>
#include <math.h>
#include "Config.h"
#include "Global.h"

unsigned long debugTime = millis();

// Configuration of the system
void setup() {  
   initTelemetry();  
   initI2C();
   initIMU();
   initReceptor();
   initMotors();
}

// Main loop
void loop() {
  updateIMU();
  
  txCommand = getTXCommand();
  switch (txCommand) {
    case ARM:
      armMotors();
      break;
    case DISARM:
      disarmMotors();
      break;
    case HALT:
      haltMotors();
      break;
    case TEST_MOTORS:
      testMotors();
      break;
  }


  if ((millis() - debugTime) > 100) {
    Serial.print(ypr[PITCH]);
    Serial.print("  ");
    Serial.print(ypr[ROLL]);
    Serial.print("  ");
    Serial.print(ypr[YAW]);
    Serial.println();
    debugTime = millis();
  }


}
