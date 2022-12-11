//==============================================================================================
// SET PINS
//
// PIN ARRAY setup = { TRAIN-1, TRAIN-2, TRAIN-3, TRAIN-4 }

const byte POT[] = { 12, 14, 27, 13 };  // Potentiometer for Speed/Throttle

const byte DIR[] = { 12, 14, 27, 13 };  // Toggle switch for Direction

const byte LIGHT[] = { 12, 14, 27, 13 };  // Toggle switch for Headlight

const byte MOMENTARY[] = { 12, 14, 27, 13 };  // Momentary swtich

#define pairPIN 22   // Connected to a Momentary switch for pairing Locomotives during operation
#define statusLED 5  // Led to indicate when atleast one Locomotive is connected

//==============================================================================================
// Debug options can be commented out if not required
#define ESPNOW_DEBUG
#define CHANNEL_DEBUG
//==============================================================================================

// Number of Trains to be controlled
#define ControlNumber 4
// Data is sent in Pulse width similar to conventional RC systems
#define ppmMin 1000
#define ppmMid 1500
#define ppmMax 2000