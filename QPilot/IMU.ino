//////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  I2C
//
//             Author: J. Arellano-Verdejo (J@Vo)
//         Created on: April 7, 2015
//  Last modification: April 8, 2015
//  
//////////////////////////////////////////////////////////////////////////////////////////////////////

int16_t accData[3];    // Accelerometer data
int16_t gyroData[3];   // Gyroscope data
int16_t magData[3];    // Magnetometer data

float gyro[2], mag[3];
float accX, accY, accZ;
float magX, magY, magZ;
float accRoll, accPitch;
float heading;

unsigned long accTime = millis();
unsigned long gyrTime = micros();
unsigned long magTime = millis();

unsigned long dtAnt = millis();
float dt;

/*
  
  initIMU()
  
  Initializes the IMU system
  
*/
void initIMU() {
  initACC();
  initGYRO();
  initMAG();
}

/*
  
  updateIMU()
  
  Updates the IMU's readings and angles
  
*/
void updateIMU() {

  // read ACC data (50Hz update rate)
  if ((millis() - accTime) > 20) {
    readACC(accData);
    accX = accData[0];
    accY = accData[1];
    accZ = accData[2];
    accTime = millis();
  }
  
  // read GYRO data (800Hz update rate)
  if ((micros() - gyrTime) > 1300){  
    readGYRO(gyroData);
    gyro[0] = gyroData[0] / 14.375;  // 14.375 = Sensitivity (view datasheet)
    gyro[1] = gyroData[1] / 14.375;    
    gyrTime = micros();
  }

  // read MAG data (10Hz update rate)
  if ((millis() - magTime) > 100) {
    readMAG(magData);
    magX = magData[0] * 0.92;  // 0.92 = Digital resolution (view datasheet)
    magY = magData[1] * 0.92;
    magZ = magData[2] * 0.92;
    magTime = millis(); 
  }

  // Heading angle
  heading = atan2(magY, magX);
  if(heading < 0)
    heading += 2*PI;
    // Check for wrap due to addition of declination.
  if(heading > 2*PI)
    heading -= 2*PI;
   
  // Convert radians to degrees for readability.
  heading = heading * 180/M_PI;   

    
  // the angles of pitch and roll are estimated
  accRoll = (atan(-accX/sqrt(pow(accY,2) + pow(accZ,2)))*RAD_TO_DEG)+OFFSET_ROLL;
  accPitch = (atan(accY/sqrt(pow(accX,2) + pow(accZ,2)))*RAD_TO_DEG)+OFFSET_PITCH;

  // complementary filter
  dt = (millis() - dtAnt) / 1000.0;
  ypr[ROLL] = 0.98 * (ypr[ROLL] + gyro[1] * dt) + (0.02 * accRoll);
  ypr[PITCH] = 0.98 * (ypr[PITCH] + gyro[0] * dt) + (0.02 * accPitch);
  ypr[YAW] = 0.98 * (heading + gyro[2] * dt) + (0.02 * heading);
  dtAnt = millis();
  
}

