//////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Motors
//
//             Author: J. Arellano-Verdejo (J@Vo)
//         Created on: April 6, 2015
//  Last modification: April 8, 2015
//  
//////////////////////////////////////////////////////////////////////////////////////////////////////

/*
  
  initMotors()
  
  Initializes the terminals where are attached the motors
  
*/
void initMotors() {
  pinMode(MOTOR_1, OUTPUT);
  pinMode(MOTOR_2, OUTPUT);
  pinMode(MOTOR_3, OUTPUT);
  pinMode(MOTOR_4, OUTPUT);
  
  analogWrite(MOTOR_1, MOTOR_DISARMED);
  analogWrite(MOTOR_2, MOTOR_DISARMED);
  analogWrite(MOTOR_3, MOTOR_DISARMED);
  analogWrite(MOTOR_4, MOTOR_DISARMED);
  
}

/*
  
  armMotors()
  
  Arms the motors
  
*/  
void armMotors() {
  if (isArmed == 0) {
    isArmed = 1;
    analogWrite(MOTOR_1, MOTOR_ARMED);
    analogWrite(MOTOR_2, MOTOR_ARMED);
    analogWrite(MOTOR_3, MOTOR_ARMED);
    analogWrite(MOTOR_4, MOTOR_ARMED);
  }
}

/*
  
  disarmMotors()
  
  Disarms the motors
  
*/
void disarmMotors() {
  if (isArmed == 1) {
    isArmed = 0;
    analogWrite(MOTOR_1, MOTOR_DISARMED);
    analogWrite(MOTOR_2, MOTOR_DISARMED);
    analogWrite(MOTOR_3, MOTOR_DISARMED);
    analogWrite(MOTOR_4, MOTOR_DISARMED);
  }
}

/*
  
  haltMotors()
  
  Halt the motors
  
*/
void haltMotors() {
  // Disarm motors
  analogWrite(MOTOR_1, MOTOR_DISARMED);
  analogWrite(MOTOR_2, MOTOR_DISARMED);
  analogWrite(MOTOR_3, MOTOR_DISARMED);
  analogWrite(MOTOR_4, MOTOR_DISARMED);
    
  // Infinite loop (It's necessary unplug the battery to restart the system)
  while(1){}
}

/*
  
  testMotors()
  
  Write 'value' data in 'motor' (PWM 0-255)
  
*/
void testMotors() {
  if (isArmed == 0) {
    delay(1000);
    for (byte i=1; i<=4; i++) {
      writeMotor(i, MOTOR_ARMED);
      delay(2000);
      writeMotor(i, MOTOR_DISARMED);
      delay(1000);
    }
    disarmMotors();
  } 
}

/*
  
  writeMotor()
  
  Write 'value' data in 'motor' (PWM 0-255)
  
*/
void writeMotor(int8_t motor, int8_t value) {
  switch (motor) {
    case 1:
      analogWrite(MOTOR_1, value);
      break;
    case 2:
      analogWrite(MOTOR_2, value);
      break;
    case 3:
      analogWrite(MOTOR_3, value);
      break;
    case 4:
      analogWrite(MOTOR_4, value);
      break;
  }
}


