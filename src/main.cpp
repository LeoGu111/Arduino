#include <display.h>
#include <Timer.h>

//Display Setup---------------------------------

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

 //RTC Setup------------------------------------

RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

//----------------------------------------------

void setup() 
{
//Start der Seriellen Kommunikation
Serial.begin(115200);

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

//Fehlermeldung auf die Serielleschnittstelle wenn der RTC nicht gefunden wird 
display_RTC_Start_sequenz();
}


void loop()
{
std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();


HomeBildschirm();
delay(3000);
int X = 0;
Menue_1(X);
delay(1000);
int Y = 22;
Menue_1(Y);
delay(1000);
int Z = 40;
Menue_1(Z);
delay(1000);

SubMenue_1_1(X, 1,0,0, 1,50,0, 2,0,0);
delay(1000);
SubMenue_1_1(Y, 1,0,0, 1,50,0, 2,0,0);
delay(1000);
SubMenue_1_1(Z, 1,0,0, 1,50,0, 2,0,0);
delay(1000);

std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end_time - start_time;
    
    std::cout << "Elapsed time: " << elapsed_seconds.count() << " seconds." << std::endl;
}
