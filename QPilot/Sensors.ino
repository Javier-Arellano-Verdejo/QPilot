//////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Sensors
//
//             Author: J. Arellano-Verdejo (J@Vo)
//         Created on: February 26, 2015
//  Last modification: April 10, 2015
//  
//////////////////////////////////////////////////////////////////////////////////////////////////////

/*
  
  I2C Accelerometer BMA180 support functions
  
*/
void initACC() {
  uint8_t control;
  
  delay(10);
  writeI2C(0x40, 0x0D, 1<<4); // register: ctrl_reg0  -- value: set bit ee_w to 1 to enable writing
  delay(5);
  
  readI2C(0x40, 0x20, 1, &control);
  control = control & 0x0F;        // save tcs register
  control = control | (0x00 << 4); // set low pass filter to 10Hz (bits value = 0000xxxx)
  writeI2C(0x40, 0x20, control);
  delay(5);
  
  readI2C(0x40, 0x30, 1, &control);
  control = control & 0xFC;        // save tco_z register
  control = control | 0x00;        // set mode_config to 0
  writeI2C(0x40, 0x30, control);  
  delay(5); 
  
  readI2C(0x40, 0x35, 1, &control);
  control = control & 0xF1;        // save offset_x and smp_skip register
  control = control | (0x04 << 1); // set range to 4G
  writeI2C(0x40, 0x35, control);
  delay(5); 
}

void readACC(int16_t *accData) { 
   byte result[6];

   readI2C(0x40, 0x02, 6, result);
    
   accData[0] = (result[0] | result[1] << 8) >> 2;
   accData[1] = (result[2] | result[3] << 8) >> 2;
   accData[2] = (result[4] | result[5] << 8) >> 2;

}

/*
  
  I2C Accelerometer ITG3205 support functions
  
*/
void initGYRO() {
  delay(10);
  
  // Gyro reset 0x80
  writeI2C(0x68, 0x3E, 0x00);
  delay(60);
  
  // Sample div
  writeI2C(0x68, 0x15, 0x07);
  delay(5);
   
  // Low pass filter to 10hz = 0x05 (bits 0, 1 and 2)
  // FL_SEL = 0x03 << 3 = 0x18 (bits 3 and 4) for proper operation 0x18 + 0x05
  writeI2C(0x68, 0x16, 0x18); 
  delay(5);
  
  // Disable interrupts
  writeI2C(0x68, 0x17, 0x00);
  delay(5);
    
  // Gyro config PLL with Z Gyro reference
  writeI2C(0x68, 0x3E, 0x03);
  delay(100);

}

void readGYRO(int16_t *gyroData) {
   byte result[6];

   readI2C(0x68, 0x1D, 6, result);
    
   gyroData[0] = (result[0] << 8) | result[1];
   gyroData[1] = (result[2] << 8) | result[3];
   gyroData[2] = (result[4] << 8) | result[5];
  
}

/*
  
  I2C Magnetometer HMC5883 support functions
  
*/
void initMAG() { 
  delay(100);
  writeI2C(0x1E, 0x01, 0x20);  // Gain = 1.3
  writeI2C(0X1E, 0x02, 0x00);  // Continuous-Measurement Mode
}

void readMAG(int16_t *magData) {
   byte result[6];

   readI2C(0x1E, 0x03, 6, result);

   magData[0] = (result[0] << 8) | result[1];  // x
   magData[1] = (result[4] << 8) | result[5];  // y
   magData[2] = (result[2] << 8) | result[3];  // z

}
