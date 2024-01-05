#include <display.h>
#include <Timer.h>

//Display Setup-----------------------------------------------------------------------------------------------------

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//RTC Setup---------------------------------------------------------------------------------------------------------

RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

//------------------------------------------------------------------------------------------------------------------

std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
std::chrono::steady_clock::time_point target_time = start_time + std::chrono::seconds(30);

bool countdownStarted = false;




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
float HMS_1 = 0;
pinMode(14, INPUT);
}

void loop() {
  std::chrono::steady_clock::time_point current_time = std::chrono::steady_clock::now();
















delay(1400);
  
  if (digitalRead(14) == HIGH) {
    // Button pressed, start or restart the countdown
    start_time = current_time;
    target_time = start_time + std::chrono::seconds(30);
    countdownStarted = true;
    Serial.println("Countdown started.");
  }

  if (countdownStarted && current_time < target_time) {
    // Calculate remaining time
    std::chrono::duration<double> remaining_seconds = target_time - current_time;

    // Display the remaining time
    Serial.print("Remaining time: ");
    Serial.print(remaining_seconds.count());
    Serial.println(" seconds.");
  } else {
    countdownStarted = false;
    Serial.println("Countdown finished.");
  }

  delay(100); // Kurze Verzögerung, um die Schleife zu verlangsamen (kann je nach Anforderungen angepasst werden)
}
