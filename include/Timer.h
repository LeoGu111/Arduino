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

Time convertFromIndustrialHours(double long industrialHours);
void Timer_Main();

extern long double Timer_1;
extern long double Timer_2;
extern long double Timer_3;

extern unsigned long previousMillis; // Variable zum Speichern der letzten Zeitmessung
extern const unsigned long interval; // Intervall in Millisekunden (hier 1 Sekunde)



#endif