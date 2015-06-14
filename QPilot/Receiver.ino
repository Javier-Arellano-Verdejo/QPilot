//////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Receiver
//
//             Author: J. Arellano-Verdejo (J@Vo)
//         Created on: April 6, 2015
//  Last modification: April 8, 2015
//  
//////////////////////////////////////////////////////////////////////////////////////////////////////

// ToDo: For config file
#define THR 0  // |
#define ROL 1  // |
#define PIT 2  // |--> Index of the rxChannelData to access the radio information
#define YAW 3  // |
#define AX1 4  // |

#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))  // clear bit in byte sfr memory
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))   // set bit in byte sfr memory

volatile byte rxChannel[RX_CHANNELS] = {RX_THR, RX_ROL, RX_PIT, RX_YAW, RX_AX1};
volatile byte rxCurrentState[RX_CHANNELS] = {0, 0, 0, 0, 0};
volatile int rxPreviousState[RX_CHANNELS] = {0, 0, 0, 0, 0};

byte tmpPinData;  // Temporal variable for incoming data

/*
  initReceptor()
  
  Initializes the incoming ports and configures the interrupts to handle the RX information
*/
void initReceptor() {
  for (uint8_t i = 0; i < RX_CHANNELS; i++) {
    pinMode(rxChannel[i], INPUT);  // Define as input
    digitalWrite(rxChannel[i], HIGH);  // Connect the internal Pull-Up rasistor
  }

  sbi(PCICR, PCIE2);  // Enable interrupt PCI2 
  sbi(PCMSK2, PCINT18);  // Set the interrupt control bits for pins 2, 4-7
  sbi(PCMSK2, PCINT20);
  sbi(PCMSK2, PCINT21);
  sbi(PCMSK2, PCINT22);
  sbi(PCMSK2, PCINT23);
}

/*
  getTXCommand()
  
  Gets the command introduced by the radio
*/
TX_COMMAND getTXCommand() {
  // Arm command 
  //
  //      |
  //   o  |  o
  //  /   |   \
  //
  if (rxChannelData[THR] <= THR_MIN && rxChannelData[YAW] <= YAW_MIN && 
      rxChannelData[PIT] <= PIT_MIN && rxChannelData[ROL] >= ROL_MAX) {
    return ARM;
  }
  
  // Disarm command
  //
  //      |
  //   o  |  o
  //    \ | /
  //      
  if (rxChannelData[THR] <= THR_MIN && rxChannelData[YAW] >= YAW_MAX && 
      rxChannelData[PIT] <= PIT_MIN && rxChannelData[ROL] <= ROL_MIN) {
    return DISARM;
  }
  
  // Halt command
  //
  //  \   |   /
  //   o  |  o
  //      |

  if (rxChannelData[THR] >= THR_MAX && rxChannelData[YAW] <= YAW_MIN && 
      rxChannelData[PIT] >= PIT_MAX && rxChannelData[ROL] >= ROL_MAX) {
    return HALT;
  }
  
  // Test motors command
  //
  //      |   /
  //   o  |  o
  //  /   |
  if (rxChannelData[THR] <= THR_MIN && rxChannelData[YAW] <= YAW_MIN && 
      rxChannelData[PIT] >= PIT_MAX && rxChannelData[ROL] >= ROL_MAX) {
    return TEST_MOTORS;
  }
  
    
}

/*
  Interrupt Service Routine for receive and analyze the incoming RX information
*/
ISR (PCINT2_vect) {
  for (uint8_t i = 0; i < RX_CHANNELS; i++) {
    tmpPinData = digitalRead(rxChannel[i]);
    if (tmpPinData == 1 && rxCurrentState[i] == 0) {
      rxPreviousState[i] = micros();
      rxCurrentState[i] = 1;    
    } else if (tmpPinData == 0 && rxCurrentState[i] == 1){
      rxChannelData[i] = micros() - rxPreviousState[i];
      rxCurrentState[i] = 0;
    }
  }
}
