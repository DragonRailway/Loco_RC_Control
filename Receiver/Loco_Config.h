//==============================================================================================

#define pairPIN 22   // Connected to a Momentary switch for pairing Locomotives during operation
#define statusLED 5  // Led to indicate when atleast one Locomotive is connected

//==============================================================================================
// Debug options can be commented out if not required
#define ESPNOW_DEBUG
#define CHANNEL_DEBUG
//==============================================================================================
// Set LocoNumber
#define LocoNumber 1

// Data is Received in Pulse width similar to conventional RC systems
#define ppmMin 1000
#define ppmMid 1500
#define ppmMax 2000

