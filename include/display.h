#ifndef ESP32_Display_00
#define ESP32_Display_00

//-------------------------------------------------------------------------------

//  #Includes:

//-------------------------------------------------------------------------------

#include <Timer.h>
#include <encoder.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <RTClib.h>
#include <Adafruit_NeoPixel.h>

//-------------------------------------------------------------------------------

//  #defines

//-------------------------------------------------------------------------------

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1    // Reset pin # (or -1 if sharing reset pin)
#define Menue_eintrag_1 "Timer"
#define Menue_eintrag_2 "Ind. Timer"
#define Menue_eintrag_3 "Settings"

#define PIN_DT 35
#define PIN_CLK 34
#define PIN_SW 32

#define LED_PIN 25
#define LED_COUNT 8

struct Time_1
{
    int hours;
    int minutes;
    int seconds;
};

//-------------------------------------------------------------------------------

//  #function defines

//-------------------------------------------------------------------------------

void display_starting_screen();
void display_starting_screen_1();
void display_Start_sequenz();
void HomeBildschirm();
void display_draw_date(DateTime now);
void display_draw_time(DateTime now);
void Menue_1(int X); // = Box kordinaten 0, 22, 40
void SubMenue_1_1(int X, float H_1, float H_2, float H_3);
int center_function(Time industrie, int X);
void Menue_Timer(double Timer_1, double Timer_2, double Timer_3);
void menue_Auswahl();
void Menue_Timer_Anzeige();
void Menue_Timer_Auswahl();
void Menue_Timer_Einstellen();
void speicher_Auswahl();
void Timer_Einstellen();

extern double long floatArray[12];
extern bool countdownStarted;
extern bool Menue_Timer_1;
extern bool SUB_ACTIVE;
extern bool SUB_ACTIVE_2;
extern bool SUB_ACTIVE_3;
extern int previousState; // Vorheriger Zustand des Pins
extern int Number;
extern int pos;
extern Adafruit_SSD1306 display;
extern RTC_DS3231 rtc;
extern ESP32Encoder encoder;
extern char daysOfTheWeek[7][12];
extern bool PIN_SW_PF;
extern int anzahl_timer;

#endif