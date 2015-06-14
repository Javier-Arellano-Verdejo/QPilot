//////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Config.h
//
//             Author: J. Arellano-Verdejo (J@Vo)
//         Created on: April 7, 2015
//  Last modification: April 7, 2015
//  
//////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __CONFIG_H__
#define __CONFIG_H__

/* --- MOTOR PORTS--------------------------------------------------------------------------------- */
#define MOTOR_1 10  // Output pins of the MultiWii controller where are the motors attached
#define MOTOR_2 11  // 
#define MOTOR_3 3   // 
#define MOTOR_4 9   //

/* --- MOTOR LEVELS ------------------------------------------------------------------------------- */
#define MOTOR_DISARMED 125
#define MOTOR_ARMED 140
#define MOTOR_MIN_COMMAND 140
#define MOTOR_MAX_COMMAND 140

/* --- RECEIVER PORT ------------------------------------------------------------------------------ */
#define RX_THR 2  // PCINT18  |
#define RX_ROL 4  // PCINT20  |
#define RX_PIT 5  // PCINT21  |--> Inputs of the MultiWii where are connected the receiver channels
#define RX_YAW 6  // PCINT22  |
#define RX_AX1 7  // PCINT23  |

/* --- RADIO CALIBRATION -------------------------------------------------------------------------- */
#define THR_MAX 1880  //  |
#define THR_MID 1470  //  |--> Throttle calibration
#define THR_MIN 1060  //  |

#define ROL_MAX 1890  //  |
#define ROL_MID 1478  //  |--> Roll calibation
#define ROL_MIN 1060  //  |

#define PIT_MAX 1880  //  |
#define PIT_MID 1470  //  |--> Pitch calibration
#define PIT_MIN 1060  //  |

#define YAW_MAX 1880  //  |
#define YAW_MID 1464  //  |--> Yaw calibration
#define YAW_MIN 1060  //  |

#define AX1_MAX 1880  //  |--> Aux1 calibration
#define AX1_MIN 1060  //  |

/* --- RECEIVER CHANNELS -------------------------------------------------------------------------- */
#define RX_CHANNELS 5

/* --- TELEMETRY ---------------------------------------------------------------------------------- */
#define TELEMETRY
#define TELEMETRY_PORT Serial
#define TELEMETRY_PORT_SPEED 115200

/* --- YAW, PITCH, AND ROLL OFFSETS --------------------------------------------------------------- */
#define OFFSET_PITCH 2.2
#define OFFSET_ROLL 0.7

/* --- DECLINATION ANGLE FOR MAGNETOMETER --------------------------------------------------------- */
#define DECLINATION_ANGLE 0

#endif
