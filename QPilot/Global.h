//////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Global.h
//
//             Author: J. Arellano-Verdejo (J@Vo)
//         Created on: April 7, 2015
//  Last modification: April 8, 2015
//  
//////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __GLOBAL_H__
#define __GLOBAL_H__

// Index to access the YPR angles
#define YAW 0   // |
#define PITCH 1 // |--> index for access to the ypr data
#define ROLL 2  // |

// Constant to convert radians to degrees
#define RAD_TO_DEG = 57.295779

// Radio TX commands
enum TX_COMMAND {
  ARM, DISARM, HALT, TEST_MOTORS
};

// System armed and disarmed
uint8_t isArmed = 0;

// Receiver variables
volatile int rxChannelData[5] = {0, 1500, 1500, 1500, 1000};
TX_COMMAND txCommand;

// IMU variables
float ypr[3] = {0, 0, 0};  // yaw, pitch and roll data from IMU

#endif
