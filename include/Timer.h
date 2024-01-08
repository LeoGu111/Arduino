#ifndef ESP32_Timer_Funktion
#define ESP32_Timer_Funktion

//-------------------------------------------------------------------------------

//  #Includes:

//-------------------------------------------------------------------------------

#include <iostream>
#include <Arduino.h>

//-------------------------------------------------------------------------------

//  #defines

//-------------------------------------------------------------------------------

struct Time {
    int hours;
    int minutes;
    int seconds;
};

//-------------------------------------------------------------------------------

//  #function defines

//-------------------------------------------------------------------------------

Time convertFromIndustrialHours(double industrialHours);
void Timer_Main();

extern double Timer_1;
extern double Timer_2;
extern double Timer_3;

extern unsigned long previousMillis; // Variable zum Speichern der letzten Zeitmessung
extern const unsigned long interval; // Intervall in Millisekunden (hier 1 Sekunde)



#endif