#include "display.h"
#include "RTClib.h"
 
void HomeBildschirm();
void display_draw_date(DateTime now);
void display_draw_time(DateTime now);
void display_starting_screen();


RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
 
#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
#define OLED_RESET    -1  // Reset pin # (or -1 if sharing reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
 
 
void setup() 
{
 
Serial.begin(9600);
 
if (! rtc.begin()) {
Serial.println("Couldn't find RTC");
while (1);              
}
 
if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) 
{ 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
}

display_starting_screen();

}
 
