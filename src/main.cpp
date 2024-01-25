#include <display.h>
#include <wlan.h>
#include <neoplixel.h>

//--------------------------------------------------------------------------------------------------------------------------------------
// Globale Variablen -------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------
double long Timer_1 = 0;                                                                         // Aktiver Timer 1
double long Timer_2 = 0;                                                                         // Aktiver Timer 2
double long Timer_3 = 0;                                                                         // Aktiver Timer 3
double long Timer_1_1 = 0;                                                                       // reference für Timer 1
double long Timer_2_1 = 0;                                                                       //  reference für Timer 2
double long Timer_3_1 = 0;                                                                       //  reference für Timer 3
unsigned long previousMillis = 0;                                                                // Variable zum Speichern der letzten Zeitmessung
const unsigned long interval = 1000;                                                             // Intervall in Millisekunden (hier 1 Sekunde)
int Number = 1;                                                                                  // Nummer für die speicher übergabe von dem Timer Array
int pos = 0;                                                                                     // position vom Encoder
double long TimerArray[12] = {60, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 3600, 7200}; // Timer Array
int anzahl_timer = sizeof(TimerArray) / sizeof(TimerArray[0]);                                   // Wie viele Timer vorhanden sind
bool Menue_Timer_1 = 0;                                                                          // Menue das die laufenden Timer anzeigt EIN
bool SUB_ACTIVE = 0;                                                                             // Menue wo man timer auswählen kann um sie zustarten EIN
bool SUB_ACTIVE_2 = 0;                                                                           // Menue wo man die timer auswählen kann um sie ein zustellen EIN
bool SUB_ACTIVE_3 = 0;                                                                           // Menue wo man den speicher ort wählen kann
int previousState = LOW;                                                                         // Vorheriger Zustand des Pins
unsigned long lastDebounceTime = 0;                                                              // Initialize the last debounce time
int lastPosition = 0;                                                                            // Initialize the last position
const int debounceDelay = 75;                                                                    // Debounce delay in milliseconds
bool PIN_SW_PF = HIGH;                                                                           // PIN vom enconder Positive Flanke
double long shortestTimer = 0;                                                                   // Kürzester laufendner Timer
double long Neuer_shortest_Timer = 0;                                                            // referenz timer
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------

// Wlan Setup--------------------------------------------------------------------------------------------------------

// WLAN DATEN EINGEBEN
const char *ssid = "iPhone von Leo";
const char *password = "Schule2023";
AsyncWebServer server(80);

// Neopixel Setup--------------------------------------------------------------------------------------------------------

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800);

// Display Setup-----------------------------------------------------------------------------------------------------

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// RTC Setup---------------------------------------------------------------------------------------------------------

RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Encoder Setup--------------------------------------------------------------------------------------------------------

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

    // Einlesen der Taster für direkt auswahl von den Timern

    pinMode(PIN_Timer_1, INPUT_PULLDOWN);
    pinMode(PIN_Timer_2, INPUT_PULLDOWN);
    pinMode(PIN_Timer_3, INPUT_PULLDOWN);

    // Setup vom encoder
    Setup_Encoder();

    // Gerät versucht eine verbindung zum Wlan herzustellen nach 15 sekund gibt es auf
    // und startet sein eigenes Wlan
    connectToWiFi();

    // Nach dem es Wlan hat startet es einen Webserver
    webserverstart();

    // Zeigt eine Kurze start seqeunz an
    display_Start_sequenz();

    // Zum setzen der Aktuellen uhrzeit bitte das untens stehende ein setzen
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop()
{
    // die nächsten 6 zeilen machen aus unserm PIN_SW eine positive Flanke
    int currentState = digitalRead(PIN_SW);
    PIN_SW_PF = HIGH;
    if (currentState == LOW && previousState == HIGH)
    {
        PIN_SW_PF = LOW;
    }

    // ab hier startet unser haupt programm
    // in der timer main wird die abgelaufene zeit seit start vom timer abgezogen
    Timer_Main();

    // die zwei fuktionen werden benutzt um die neo pixel zu steuern
    Neopixel_funtkion();
    // holt die encoder position entprellt die und schriebt die auf POS
    encoder_position();
    // meneu auswahl ist das haupt menue und menue Timer zeigt die aktiven timer an
    menue_Auswahl();
    Menue_Timer_Anzeige();
    // menue timer auswahl ist das menue wo man seine timer wählen kann und
    // speicher auswahl fragt ob man in Timer 1 oder Timer 2 oder Timer 3 staren will
    speicher_Auswahl();
    Menue_Timer_Auswahl();
    // menue timer einstellen is das menu wo man seine timer wählen kann um diese um zu speichern
    // Timer einstellen ist dazu da das man die Timmer einstellt
    Timer_Einstellen();
    Menue_Timer_Einstellen();
    // Taster funktion für schnell zugriff ind display done bildschirm
    Tasterfunktion();
    Display_Timer_Done();

    previousState = currentState;
}
