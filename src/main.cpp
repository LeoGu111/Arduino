#include <display.h>

unsigned long previousMillis = 0; // Variable zum Speichern der letzten Zeitmessung
const unsigned long interval = 1000; // Intervall in Millisekunden (hier 1 Sekunde)

//Display Setup-----------------------------------------------------------------------------------------------------

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//RTC Setup---------------------------------------------------------------------------------------------------------

RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

//------------------------------------------------------------------------------------------------------------------

// Erstelle eine Instanz des Encoders
ESP32Encoder encoder;
bool debounceEncoder(int rawPosition,  int lastPosition);
    static unsigned long lastDebounceTime = 0; // Initialize the last debounce time
    static int lastPosition = 0; // Initialize the last position
    const int debounceDelay = 50; // Debounce delay in milliseconds

int pos = 0;

//-------------------------------------------------------------------------------------------------------------------

float floatArray[12] = {1.2f, 3.4f, 5.6f, 7.8f, 9.0f, 11.1f, 13.2f, 15.3f, 17.4f, 19.5f, 20.0f, 20.5f};
bool countdownStarted = false;
bool Menue_Timer_1 = 0;
bool SUB_ACTIVE = 0;
bool SUB_ACTIVE_2 = 0;
double Timer_1 = 0;
double Timer_2 = 0;
double Timer_3 = 0;
int previousState = LOW; // Vorheriger Zustand des Pins
int Number = 1;


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
display_Start_sequenz();
float HMS_1 = 0;
pinMode(PIN_SW, INPUT);

  // Konfiguriere die Pins für den Encoder
  ESP32Encoder::useInternalWeakPullResistors = UP;
  encoder.attachSingleEdge(PIN_DT, PIN_CLK);
}

bool debounceEncoder(int rawPosition, int lastPosition) {

    unsigned long currentTime = millis();

    if (rawPosition == lastPosition) {
        lastDebounceTime = currentTime;
    }

    if (currentTime - lastDebounceTime > debounceDelay) {
        return true; // Successfully updated debounced position
    } else {
        return false; // No update of debounced position
    }

 
}

void loop() {

unsigned long currentMillis = millis(); // Aktuelle Zeit in Millisekunden
if (currentMillis - previousMillis >= interval) 
{
if (Timer_1 > 0)
{
Timer_1 = Timer_1 - 1;
previousMillis = currentMillis; // Speichere die aktuelle Zeit für den nächsten Durchlauf
}
if (Timer_2 > 0)
{
Timer_2 = Timer_2 - 1;
previousMillis = currentMillis; // Speichere die aktuelle Zeit für den nächsten Durchlauf
}
if (Timer_3 > 0)
{
Timer_3 = Timer_3 - 1;
previousMillis = currentMillis; // Speichere die aktuelle Zeit für den nächsten Durchlauf
}
}


int currentState = digitalRead(PIN_SW);
bool PIN_SW_PF = HIGH;

if (currentState == LOW && previousState == HIGH) 
{
PIN_SW_PF = LOW;
}


// Lese die aktuelle Position des Encoders
int rawPosition = encoder.getCount();
  
bool x = debounceEncoder(rawPosition, pos);

if (x == 1)
{
  if(pos<rawPosition)
  {
    pos = pos + 1;
  }
  else 
  {
    pos = pos - 1;
  }
  encoder.setCount(pos);
}


if(SUB_ACTIVE == 0 and SUB_ACTIVE_2 == 0 and Menue_Timer_1 == 0){
    switch (pos) {
      case 0:
        HomeBildschirm();
        break;
      case 1:
        HomeBildschirm();
        break;
      case 2:
        Menue_1(0);
        break;
      case 3:
        Menue_1(22);
        break;
      case 4:
        Menue_1(40);
        break;
      default:
      if (pos < 0) {
        encoder.setCount(0);
      } else if (pos > 4) {
        encoder.setCount(4);
      }
      break;
    }
  }

if ((pos == 1 and PIN_SW_PF == 0 and SUB_ACTIVE == 0 and SUB_ACTIVE_2 == 0) or Menue_Timer_1)
{
  Menue_Timer(Timer_1/3600,Timer_2/3600,Timer_3/3600);
  if (PIN_SW_PF == 0 and Menue_Timer_1 == 1)
  {
  Menue_Timer_1 = 0;
  }
  else
  {
  Menue_Timer_1 = 1;
  }
  encoder.setCount(1);
}

if ((pos == 2 and PIN_SW_PF == 0 and SUB_ACTIVE_2 == 0) or SUB_ACTIVE == 1){
    switch (pos) {
    case 0:
      SubMenue_1_1(0, floatArray[0], floatArray[1], floatArray[2]);
      Number = 0;
      if (PIN_SW_PF == 0 and Timer_1 == 0)
      {
      Timer_1 = floatArray[Number] * 60.0 * 60.0;
      Menue_Timer_1 = 1;
      pos = -1;
      SUB_ACTIVE = 0;
      }
      else if (PIN_SW_PF == 0 and Timer_2 == 0)
      {
      Timer_2 = floatArray[Number] * 60.0 * 60.0;
      Menue_Timer_1 = 1;
      pos = -1;
      SUB_ACTIVE = 0;
      }
      else if (PIN_SW_PF == 0 and Timer_3 == 0)
      {
      Timer_3 = floatArray[Number] * 60.0 * 60.0;
      Menue_Timer_1 = 1;
      pos = -1;
      SUB_ACTIVE = 0;
      }
      
      
      break;
    case 1:
      SubMenue_1_1(20, floatArray[0], floatArray[1], floatArray[2]);
      Number = 1;
      if (PIN_SW_PF == 0 and Timer_1 == 0)
      {
      Timer_1 = floatArray[Number] * 60.0 * 60.0;
      Menue_Timer_1 = 1;
      pos = -1;
      SUB_ACTIVE = 0;
      }
      else if (PIN_SW_PF == 0 and Timer_2 == 0)
      {
      Timer_2 = floatArray[Number] * 60.0 * 60.0;
      Menue_Timer_1 = 1;
      pos = -1;
      SUB_ACTIVE = 0;
      }
      else if (PIN_SW_PF == 0 and Timer_3 == 0)
      {
      Timer_3 = floatArray[Number] * 60.0 * 60.0;
      Menue_Timer_1 = 1;
      pos = -1;
      SUB_ACTIVE = 0;
      }
      break;
    case 2:
      if (digitalRead(PIN_SW) == 0 and SUB_ACTIVE == 0)
      {
      SUB_ACTIVE = 1;
      pos = -1;
      }
      else
      {
      SubMenue_1_1(40, floatArray[0], floatArray[1], floatArray[2]);
      Number = 2;
      if (PIN_SW_PF == 0 and Timer_1 == 0)
      {
      Timer_1 = floatArray[Number] * 60.0 * 60.0;
      Menue_Timer_1 = 1;
      pos = -1;
      SUB_ACTIVE = 0;
      }
      else if (PIN_SW_PF == 0 and Timer_2 == 0)
      {
      Timer_2 = floatArray[Number] * 60.0 * 60.0;
      Menue_Timer_1 = 1;
      pos = -1;
      SUB_ACTIVE = 0;
      }
      else if (PIN_SW_PF == 0 and Timer_3 == 0)
      {
      Timer_3 = floatArray[Number] * 60.0 * 60.0;
      Menue_Timer_1 = 1;
      pos = -1;
      SUB_ACTIVE = 0;
      }
      }
      break;
    case 3:
      SubMenue_1_1(0, floatArray[3], floatArray[4], floatArray[5]);
      Number = 3;
      if (PIN_SW_PF == 0 and Timer_1 == 0)
      {
      Timer_1 = floatArray[Number] * 60.0 * 60.0;
      Menue_Timer_1 = 1;
      pos = -1;
      SUB_ACTIVE = 0;
      }
      else if (PIN_SW_PF == 0 and Timer_2 == 0)
      {
      Timer_2 = floatArray[Number] * 60.0 * 60.0;
      Menue_Timer_1 = 1;
      pos = -1;
      SUB_ACTIVE = 0;
      }
      else if (PIN_SW_PF == 0 and Timer_3 == 0)
      {
      Timer_3 = floatArray[Number] * 60.0 * 60.0;
      Menue_Timer_1 = 1;
      pos = -1;
      SUB_ACTIVE = 0;
      }
       
      break;
    case 4:
      SubMenue_1_1(20, floatArray[3], floatArray[4], floatArray[5]);
      Number = 4;
      if (PIN_SW_PF == 0 and Timer_1 == 0)
      {
      Timer_1 = floatArray[Number] * 60.0 * 60.0;
      Menue_Timer_1 = 1;
      pos = -1;
      SUB_ACTIVE = 0;
      }
      else if (PIN_SW_PF == 0 and Timer_2 == 0)
      {
      Timer_2 = floatArray[Number] * 60.0 * 60.0;
      Menue_Timer_1 = 1;
      pos = -1;
      SUB_ACTIVE = 0;
      }
      else if (PIN_SW_PF == 0 and Timer_3 == 0)
      {
      Timer_3 = floatArray[Number] * 60.0 * 60.0;
      Menue_Timer_1 = 1;
      pos = -1;
      SUB_ACTIVE = 0;
      }
      break;
    case 5:
      SubMenue_1_1(40,  floatArray[3], floatArray[4], floatArray[5]);
      Number = 5;
      if (PIN_SW_PF == 0 and Timer_1 == 0)
      {
      Timer_1 = floatArray[Number] * 60.0 * 60.0;
      Menue_Timer_1 = 1;
      pos = -1;
      SUB_ACTIVE = 0;
      }
      else if (PIN_SW_PF == 0 and Timer_2 == 0)
      {
      Timer_2 = floatArray[Number] * 60.0 * 60.0;
      Menue_Timer_1 = 1;
      pos = -1;
      SUB_ACTIVE = 0;
      }
      else if (PIN_SW_PF == 0 and Timer_3 == 0)
      {
      Timer_3 = floatArray[Number] * 60.0 * 60.0;
      Menue_Timer_1 = 1;
      pos = -1;
      SUB_ACTIVE = 0;
      }
      break;
    case 6:
      SubMenue_1_1(0, floatArray[6], floatArray[7], floatArray[8]);
      Number = 6;
      if (PIN_SW_PF == 0 and Timer_1 == 0)
      {
      Timer_1 = floatArray[Number] * 60.0 * 60.0;
      Menue_Timer_1 = 1;
      pos = -1;
      SUB_ACTIVE = 0;
      }
      else if (PIN_SW_PF == 0 and Timer_2 == 0)
      {
      Timer_2 = floatArray[Number] * 60.0 * 60.0;
      Menue_Timer_1 = 1;
      pos = -1;
      SUB_ACTIVE = 0;
      }
      else if (PIN_SW_PF == 0 and Timer_3 == 0)
      {
      Timer_3 = floatArray[Number] * 60.0 * 60.0;
      Menue_Timer_1 = 1;
      pos = -1;
      SUB_ACTIVE = 0;
      }
      break;
    case 7:
      SubMenue_1_1(20, floatArray[6], floatArray[7], floatArray[8]);
      Number = 7;
      if (PIN_SW_PF == 0 and Timer_1 == 0)
      {
      Timer_1 = floatArray[Number] * 60.0 * 60.0;
      Menue_Timer_1 = 1;
      pos = -1;
      SUB_ACTIVE = 0;
      }
      else if (PIN_SW_PF == 0 and Timer_2 == 0)
      {
      Timer_2 = floatArray[Number] * 60.0 * 60.0;
      Menue_Timer_1 = 1;
      pos = -1;
      SUB_ACTIVE = 0;
      }
      else if (PIN_SW_PF == 0 and Timer_3 == 0)
      {
      Timer_3 = floatArray[Number] * 60.0 * 60.0;
      Menue_Timer_1 = 1;
      pos = -1;
      SUB_ACTIVE = 0;
      }
      break;
    case 8:
      SubMenue_1_1(40,floatArray[6], floatArray[7], floatArray[8]);
      Number = 8;
      if (PIN_SW_PF == 0 and Timer_1 == 0)
      {
      Timer_1 = floatArray[Number] * 60.0 * 60.0;
      Menue_Timer_1 = 1;
      pos = -1;
      SUB_ACTIVE = 0;
      }
      else if (PIN_SW_PF == 0 and Timer_2 == 0)
      {
      Timer_2 = floatArray[Number] * 60.0 * 60.0;
      Menue_Timer_1 = 1;
      pos = -1;
      SUB_ACTIVE = 0;
      }
      else if (PIN_SW_PF == 0 and Timer_3 == 0)
      {
      Timer_3 = floatArray[Number] * 60.0 * 60.0;
      Menue_Timer_1 = 1;
      pos = -1;
      SUB_ACTIVE = 0;
      }
      break;
    case 9:
      SubMenue_1_1(0, floatArray[9], floatArray[10], floatArray[11]);
      Number = 9;
      if (PIN_SW_PF == 0 and Timer_1 == 0)
      {
      Timer_1 = floatArray[Number] * 60.0 * 60.0;
      Menue_Timer_1 = 1;
      pos = -1;
      SUB_ACTIVE = 0;
      }
      else if (PIN_SW_PF == 0 and Timer_2 == 0)
      {
      Timer_2 = floatArray[Number] * 60.0 * 60.0;
      Menue_Timer_1 = 1;
      pos = -1;
      SUB_ACTIVE = 0;
      }
      else if (PIN_SW_PF == 0 and Timer_3 == 0)
      {
      Timer_3 = floatArray[Number] * 60.0 * 60.0;
      Menue_Timer_1 = 1;
      pos = -1;
      SUB_ACTIVE = 0;
      }
      break;
    case 10:
      SubMenue_1_1(20, floatArray[9], floatArray[10], floatArray[11]);
      Number = 10;
      if (PIN_SW_PF == 0 and Timer_1 == 0)
      {
      Timer_1 = floatArray[Number] * 60.0 * 60.0;
      Menue_Timer_1 = 1;
      pos = -1;
      SUB_ACTIVE = 0;
      }
      else if (PIN_SW_PF == 0 and Timer_2 == 0)
      {
      Timer_2 = floatArray[Number] * 60.0 * 60.0;
      Menue_Timer_1 = 1;
      pos = -1;
      SUB_ACTIVE = 0;
      }
      else if (PIN_SW_PF == 0 and Timer_3 == 0)
      {
      Timer_3 = floatArray[Number] * 60.0 * 60.0;
      Menue_Timer_1 = 1;
      pos = -1;
      SUB_ACTIVE = 0;
      }
      break;
    case 11:
      SubMenue_1_1(40, floatArray[9], floatArray[10], floatArray[11]);
      Number = 11;
      if (PIN_SW_PF == 0 and Timer_1 == 0)
      {
      Timer_1 = floatArray[Number] * 60.0 * 60.0;
      Menue_Timer_1 = 1;
      pos = -1;
      SUB_ACTIVE = 0;
      }
      else if (PIN_SW_PF == 0 and Timer_2 == 0)
      {
      Timer_2 = floatArray[Number] * 60.0 * 60.0;
      Menue_Timer_1 = 1;
      pos = -1;
      SUB_ACTIVE = 0;
      }
      else if (PIN_SW_PF == 0 and Timer_3 == 0)
      {
      Timer_3 = floatArray[Number] * 60.0 * 60.0;
      Menue_Timer_1 = 1;
      pos = -1;
      SUB_ACTIVE = 0;
      }
      break;
      break;
    case 12:
      display.clearDisplay();
      display.setCursor(40,2);
      display.printf("back");
      display.drawRect(0, 0, 128, 19, WHITE);
      display.display();
      if(digitalRead(PIN_SW) == 0)
      {
        pos = 1;
        SUB_ACTIVE = 0;
        delay(500);
      }
       break;
    default:
        if (pos < 0) {
          encoder.setCount(0);
        } else if (pos > 12) {
          encoder.setCount(12);
        }
      break;
  }
  }

if ((pos == 3 and digitalRead(PIN_SW) == 0 and SUB_ACTIVE == 0) or SUB_ACTIVE_2 == 1){
    switch (pos) {
    case 0:
      SubMenue_1_1(0, floatArray[0], floatArray[1], floatArray[2]);
      
      break;
    case 1:
      SubMenue_1_1(20, floatArray[0], floatArray[1], floatArray[2]);
      
      break;
    case 2:
      SubMenue_1_1(40, floatArray[3], floatArray[4], floatArray[5]);
      break;
    case 3:
        SUB_ACTIVE_2 = 1;
         if (digitalRead(PIN_SW) == 0)
         {
          encoder.setCount(-1);
         }
         else
         {
         SubMenue_1_1(0, floatArray[0], floatArray[1], floatArray[2]);
         }
      break;
    case 4:
      SubMenue_1_1(20, floatArray[3], floatArray[4], floatArray[5]);
       
      break;
    case 5:
      SubMenue_1_1(40,  floatArray[3], floatArray[4], floatArray[5]);
       
      break;
    case 6:
      SubMenue_1_1(0, floatArray[6], floatArray[7], floatArray[8]);
      
      break;
    case 7:
      SubMenue_1_1(20, floatArray[6], floatArray[7], floatArray[8]);
       
      break;
    case 8:
      SubMenue_1_1(40,floatArray[6], floatArray[7], floatArray[8]);
       
      break;
    case 9:
      SubMenue_1_1(0, floatArray[9], floatArray[10], floatArray[11]);
       
      break;
    case 10:
      SubMenue_1_1(20, floatArray[9], floatArray[10], floatArray[11]);
       
      break;
    case 11:
      SubMenue_1_1(40, floatArray[9], floatArray[10], floatArray[11]);
      break;
    case 12:
      display.clearDisplay();
      display.setCursor(40,2);
      display.printf("back");
      display.drawRect(0, 0, 128, 19, WHITE);
      display.display();
      if(digitalRead(PIN_SW) == 0)
      {
        pos = 1;
        SUB_ACTIVE_2 = 0;
        delay(500);
      }
       break;
    default:
        if (pos < 0) {
          encoder.setCount(0);
        } else if (pos > 12) {
          encoder.setCount(12);
        }
      break;
  }
  }




  previousState = currentState;
}

