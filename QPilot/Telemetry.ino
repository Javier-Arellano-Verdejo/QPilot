//////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Telemetry
//
//             Author: J. Arellano-Verdejo (J@Vo)
//         Created on: February 26, 2015
//  Last modification: April 7, 2015
//  
//////////////////////////////////////////////////////////////////////////////////////////////////////

/*
  
  initTelemetry()
  
  Initializes the telemetry system
  
*/
void initTelemetry() {
   TELEMETRY_PORT.begin(TELEMETRY_PORT_SPEED); 
}

/*
  
  sendTelemetryData()
  
  Sends the telemetry information to ground control station
  
*/
void sendTelemetryData() {
}

/*
  // Para calibrar el radio
  Serial.print(rxChannelData[0]);
  Serial.print("\t");
  Serial.print(rxChannelData[1]);
  Serial.print("\t");
  Serial.print(rxChannelData[2]);
  Serial.print("\t");
  Serial.print(rxChannelData[3]);
  Serial.print("\t");
  Serial.print(rxChannelData[4]);
  Serial.println();
*/
