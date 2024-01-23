#include <display.h>
#include <wlan.h>
#include "webserver.h"
#include <ESPAsyncWebServer.h>

#define PIN_Timer_1 13
#define PIN_Timer_2 12
#define PIN_Timer_3 14

AsyncWebServer server(80);

double long Timer_1 = 0;
double long Timer_2 = 0;
double long Timer_3 = 0;
unsigned long previousMillis = 0;    // Variable zum Speichern der letzten Zeitmessung
const unsigned long interval = 1000; // Intervall in Millisekunden (hier 1 Sekunde)
int Number = 1;
int pos = 0;
double long floatArray[12] = {60, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 3600, 7200};
int anzahl_timer = sizeof(floatArray) / sizeof(floatArray[0]);
bool countdownStarted = false;
bool Menue_Timer_1 = 0;
bool SUB_ACTIVE = 0;
bool SUB_ACTIVE_2 = 0;
bool SUB_ACTIVE_3 = 0;
int previousState = LOW;            // Vorheriger Zustand des Pins
unsigned long lastDebounceTime = 0; // Initialize the last debounce time
int lastPosition = 0;               // Initialize the last position
const int debounceDelay = 75;       // Debounce delay in milliseconds
bool PIN_SW_PF = HIGH;
double long shortestTimer = 0;
double long Neuer_shortest_Timer = 0;
bool timer_neu_Ausgewaehlt = 0;

void updateLEDsBasedOnShortestTimer();
void findshortestTimer();

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800);

// Display Setup-----------------------------------------------------------------------------------------------------

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// RTC Setup---------------------------------------------------------------------------------------------------------

RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

//------------------------------------------------------------------------------------------------------------------

ESP32Encoder encoder;

//------------------------------------------------------------------------------------------------------------------


void setup()
{
    // Start der Seriellen Kommunikation
    Serial.begin(115200);

    // Fehlermeldung auf die Serielleschnittstelle wenn der RTC nicht gefunden wird
    if (!rtc.begin())
    {
        Serial.println("Couldn't find RTC");
        while (1)
            ;
    }
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ; // Don't proceed, loop forever
    }

    pinMode(PIN_Timer_1, INPUT_PULLDOWN);
    pinMode(PIN_Timer_2, INPUT_PULLDOWN);
    pinMode(PIN_Timer_3, INPUT_PULLDOWN);

    Setup_Encoder();
    connectToWiFi();
  // Route to handle requests and provide HTML page with array values
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    String html = "<html><body><h1>Array values:</h1><ul>";
    for (size_t i = 0; i < sizeof(floatArray) / sizeof(floatArray[0]); i++) {
      html += "<li>" + String((long)floatArray[i]) + "</li>";
    }
    html += "</ul></body></html>";
    request->send(200, "text/html", html);
  });

  // Start server
  server.begin();
    display_Start_sequenz();
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop()
{
    int currentState = digitalRead(PIN_SW);
    PIN_SW_PF = HIGH;
    if (currentState == LOW && previousState == HIGH)
    {
        PIN_SW_PF = LOW;
    }

    Timer_Main();

    findshortestTimer();
    updateLEDsBasedOnShortestTimer();

    encoder_position();
    menue_Auswahl();
    Menue_Timer_Anzeige();

    speicher_Auswahl();
    Menue_Timer_Auswahl();

    Timer_Einstellen();
    Menue_Timer_Einstellen();

    if (digitalRead(PIN_Timer_1) == HIGH)
    {
        Timer_1 = floatArray[0];
        Menue_Timer_1 = 1;
    }
    if (digitalRead(PIN_Timer_2) == HIGH)
    {
        Timer_2 = floatArray[1];
        Menue_Timer_1 = 1;
    }
    if (digitalRead(PIN_Timer_3) == HIGH)
    {
        Timer_3 = floatArray[2];
        Menue_Timer_1 = 1;
    }

    Serial.printf("%d, %d, %d", digitalRead(PIN_Timer_1), digitalRead(PIN_Timer_2), digitalRead(PIN_Timer_3));

    if ((Timer_1 != shortestTimer) and (Timer_2 != shortestTimer) and (Timer_3 != shortestTimer))
    {
        timer_neu_Ausgewaehlt = true;
    }
    else
    {
        timer_neu_Ausgewaehlt = false;
    }

    previousState = currentState;
}

// NeoPixel Anzeige----------------------------------------------------------------------
void findshortestTimer()
{

    if (Timer_1 > 0)
    {
        shortestTimer = Timer_1;

        if (timer_neu_Ausgewaehlt)
        {
            Neuer_shortest_Timer = Timer_1;
        }
    }

    if (Timer_2 > 0 && Timer_2 <= shortestTimer)
    {
        shortestTimer = Timer_2;

        if (timer_neu_Ausgewaehlt)
        {
            Neuer_shortest_Timer = Timer_2;
        }
    }

    if (Timer_3 > 0 && Timer_3 <= shortestTimer)
    {
        shortestTimer = Timer_3;
        if (timer_neu_Ausgewaehlt)
        {
            Neuer_shortest_Timer = Timer_3;
        }
    }
}

void updateLEDsBasedOnShortestTimer()
{
    int ledsToShow = map(shortestTimer, 1, Neuer_shortest_Timer, 1, LED_COUNT);

    if (Neuer_shortest_Timer <= 0)
    {
        ledsToShow = 0;
    }

    printf("%d", ledsToShow);
    // printf("%d", Neuer_shortest_Timer);
    for (int i = 0; i < LED_COUNT; i++)
    {
        if (i < ledsToShow)
        {
            strip.setPixelColor(i, strip.Color(0, 20, 0)); // Grün für abgelaufene Zeit
        }
        else
        {
            strip.setPixelColor(i, strip.Color(0, 0, 0)); // Aus für verbleibende Zeit
        }
    }
    strip.show();
}

