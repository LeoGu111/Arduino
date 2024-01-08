#include <display.h>

double Timer_1 = 0;
double Timer_2 = 0;
double Timer_3 = 0;
unsigned long previousMillis = 0; // Variable zum Speichern der letzten Zeitmessung
const unsigned long interval = 1000; // Intervall in Millisekunden (hier 1 Sekunde)
int Number = 1;
int pos = 0;
float floatArray[12] = {1.2f, 3.4f, 5.6f, 7.8f, 9.0f, 11.1f, 13.2f, 15.3f, 17.4f, 19.5f, 20.0f, 20.5f};
bool countdownStarted = false;
bool Menue_Timer_1 = 0;
bool SUB_ACTIVE = 0;
bool SUB_ACTIVE_2 = 0;
bool SUB_ACTIVE_3 = 0;
int previousState = LOW; // Vorheriger Zustand des Pins
unsigned long lastDebounceTime = 0; // Initialize the last debounce time
int lastPosition = 0; // Initialize the last position
const int debounceDelay = 50; // Debounce delay in milliseconds
bool PIN_SW_PF = HIGH;

//Display Setup-----------------------------------------------------------------------------------------------------

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//RTC Setup---------------------------------------------------------------------------------------------------------

RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

//------------------------------------------------------------------------------------------------------------------

ESP32Encoder encoder;

//------------------------------------------------------------------------------------------------------------------


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


Setup_Encoder();
display_Start_sequenz();
}


void loop() {
int currentState = digitalRead(PIN_SW);
PIN_SW_PF = HIGH;
if (currentState == LOW && previousState == HIGH) 
{
PIN_SW_PF = LOW;
}



Timer_Main();
encoder_position();
menue_Auswahl();
Menue_Timer_Anzeige();
Menue_Timer_Auswahl();
Menue_Timer_Einstellen();

  previousState = currentState;
}

