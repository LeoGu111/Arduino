#ifndef ESP32_Wlan
#define ESP32_Wlan

//-------------------------------------------------------------------------------

//  #Includes:

//-------------------------------------------------------------------------------

#include <WiFi.h>
#include <ESPAsyncWebServer.h>

//-------------------------------------------------------------------------------

//  #defines

//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------

//  #function defines

//-------------------------------------------------------------------------------

void connectToWiFi();
void startAccessPoint();
void changeWiFiCredentials(const char *newSSID, const char *newPassword);
void webserverstart();

extern AsyncWebServer server; 
extern const char *ssid;
extern const char *password;
extern double long TimerArray[12];

#endif