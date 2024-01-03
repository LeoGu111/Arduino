#include <display.h>


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
 
RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};


void setup() 
{
    
//Start der Serielle kommunikation
Serial.begin(115200);
Serial.println("1");

//Fehlermeldung auf die Serielleschnittstelle wenn der RTC nicht gefunden wird 
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


void loop()
{
HomeBildschirm();
delay(3000);
Menue_1();
delay(1000);
Menue_2();
delay(1000);
Menue_3();
delay(1000);
}
