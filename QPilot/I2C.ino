//////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  I2C
//
//             Author: J. Arellano-Verdejo (J@Vo)
//         Created on: April 7, 2015
//  Last modification: April 7, 2015
//  
//////////////////////////////////////////////////////////////////////////////////////////////////////

/*
  
  initI2C()
  
  Initializes the I2C bus system
  
*/
void initI2C() {
  Wire.begin();
  
  // fast I2C
  TWBR = ((F_CPU / 400000) - 16) / 2;  
}

/*
  
  writeI2C()
  
  Writes in the device with address 'address' in the register 'reg'  the value 'val' 
  
*/
void writeI2C(int address, byte reg, byte val) {
   Wire.beginTransmission(address);
   Wire.write(reg);
   Wire.write(val);
   Wire.endTransmission();
}

/*
  
  readI2C()
  
  Reads from the device with address 'address' of the register 'reg'  'n' bytes and store the 
  data in 'buff'
  
*/
void readI2C(int address, byte reg, int n, byte buff[]) {
   Wire.beginTransmission(address);
   Wire.write(reg);
   Wire.endTransmission();
 
   Wire.beginTransmission(address);
   Wire.requestFrom(address, n);
 
   int i = 0;
   while(Wire.available()) { 
      buff[i] = Wire.read();
      i++;
   }
 
   Wire.endTransmission();
}

