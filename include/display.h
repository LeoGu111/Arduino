#ifndef ESP32_Display_00
#define ESP32_Display_00

//-------------------------------------------------------------------------------

//  #Includes:

//-------------------------------------------------------------------------------

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <RTClib.h>
#include <time.h>

//-------------------------------------------------------------------------------

//  #defines

//-------------------------------------------------------------------------------

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
#define OLED_RESET    -1  // Reset pin # (or -1 if sharing reset pin)
#define Menue_eintrag_1 "Timer"
#define Menue_eintrag_2 "Ind. Timer"
#define Menue_eintrag_3 "Settings"

//-------------------------------------------------------------------------------

//  #defines

//-------------------------------------------------------------------------------

void display_starting_screen();
void display_starting_screen_1();
void display_RTC_Start_sequenz();
void HomeBildschirm();
void display_draw_date(DateTime now);
void display_draw_time(DateTime now);
void Menue_1(int X); // = Box kordinaten 0, 22, 40
void SubMenue_1_1(int X, int H_1, int M_1, int S_1, int H_2, int M_2, int S_2, int H_3, int M_3, int S_3);
int center_function(int H_1,int M_1,int S_1);


extern Adafruit_SSD1306 display;
 
 extern RTC_DS3231 rtc;
extern char daysOfTheWeek[7][12];



#endif