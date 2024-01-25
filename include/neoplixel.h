#ifndef ESP32_Neopixel
#define ESP32_Neopixel

//-------------------------------------------------------------------------------

//  #Includes:

//-------------------------------------------------------------------------------

#include <Adafruit_NeoPixel.h>

//-------------------------------------------------------------------------------

//  #defines

//-------------------------------------------------------------------------------

#define LED_PIN 25
#define LED_COUNT 8

//-------------------------------------------------------------------------------

//  #function defines

//-------------------------------------------------------------------------------


void Neopixel_funtkion();
void findshortestTimer();
void updateLEDsBasedOnShortestTimer();


extern long double shortestTimer;
extern long double Neuer_shortest_Timer;
extern Adafruit_NeoPixel strip;
extern long double Timer_1;
extern long double Timer_2;
extern long double Timer_3;
extern long double Timer_1_1;
extern long double Timer_2_1;
extern long double Timer_3_1;


#endif