#ifndef ESP32_encoder_Funktion
#define ESP32_encoder_Funktion

//-------------------------------------------------------------------------------

//  #Includes:

//-------------------------------------------------------------------------------

#include <ESP32Encoder.h>

//-------------------------------------------------------------------------------

//  #defines

//-------------------------------------------------------------------------------



//-------------------------------------------------------------------------------

//  #function defines

//-------------------------------------------------------------------------------

bool debounceEncoder(int rawPosition,  int lastPosition);
void encoder_position();
void Setup_Encoder();

extern ESP32Encoder encoder;
extern unsigned long lastDebounceTime; // Initialize the last debounce time
extern int lastPosition; // Initialize the last position
extern const int debounceDelay; // Debounce delay in milliseconds




#endif