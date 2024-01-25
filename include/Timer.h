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

struct Time
{
    int hours;
    int minutes;
    int seconds;
};

//-------------------------------------------------------------------------------

//  #function defines

//-------------------------------------------------------------------------------

Time convert_to_HMS(long double totalSeconds);
void Timer_Main();

extern long double Timer_1;
extern long double Timer_2;
extern long double Timer_3;
extern long double Timer_1_1;
extern long double Timer_2_1;
extern long double Timer_3_1;


extern unsigned long previousMillis; // Variable zum Speichern der letzten Zeitmessung
extern const unsigned long interval; // Intervall in Millisekunden (hier 1 Sekunde)

#endif