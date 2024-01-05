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

//-------------------------------------------------------------------------------------------------------------------

RotaryEncoder encoder(PIN_CLK, PIN_DT, RotaryEncoder::LatchMode::FOUR3);
static long pos = 1;

//-------------------------------------------------------------------------------------------------------------------


bool countdownStarted = false;
bool SUB_ACTIVE = 0;






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
}




void loop() {
  std::chrono::steady_clock::time_point current_time = std::chrono::steady_clock::now();

 encoder.tick();
 int newPos = encoder.getPosition();



 if (pos != newPos)
 {
 pos = newPos;
 Serial.printf("new pos = %d\n", pos);
 }

  if(SUB_ACTIVE == 0){
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
          pos = 0;
        } else if (pos > 4) {
          pos = 4;
        }
        break;
    }
  }



  if ((pos == 2 and digitalRead(PIN_SW) == 0) or SUB_ACTIVE == 1){
    switch (pos) {
    case 0:
      SubMenue_1_1(0, 0,1,0 ,0,2,0 ,0,3,0);
      
      break;
    case 1:
      SubMenue_1_1(22, 0,1,0 ,0,2,0 ,0,3,0);
      
      break;
    case 2:
       SUB_ACTIVE = 1;
         if (digitalRead(PIN_SW) == 0)
         {
          encoder.setPosition(0);
         }
         else
         {
         SubMenue_1_1(40, 0,1,0 ,0,2,0 ,0,3,0);
         }
      break;
    case 3:
      SubMenue_1_1(0, 1,1,0 ,0,2,0 ,0,3,0);
       
      break;
    case 4:
      SubMenue_1_1(22, 1,1,0 ,0,2,0 ,0,3,0);
       
      break;
    case 5:
      SubMenue_1_1(40, 1,1,0 ,0,2,0 ,0,3,0);
       
      break;
    case 6:
      SubMenue_1_1(0, 2,1,0 ,0,2,0 ,0,3,0);
      
      break;
    case 7:
      SubMenue_1_1(22, 2,1,0 ,0,2,0 ,0,3,0);
       
      break;
    case 8:
      SubMenue_1_1(40, 2,1,0 ,0,2,0 ,0,3,0);
       
      break;
    case 9:
      SubMenue_1_1(0, 3,1,0 ,0,2,0 ,0,3,0);
       
      break;
    case 10:
      SubMenue_1_1(22, 3,1,0 ,0,2,0 ,0,3,0);
       
      break;
    case 11:
      SubMenue_1_1(40, 3,1,0 ,0,2,0 ,0,3,0);
      break;
    case 12:
      display.clearDisplay();
      display.setCursor(40,2);
      display.printf("back");
      display.drawRect(0, 0, 128, 19, WHITE);
      display.display();
      if(digitalRead(PIN_SW) == 0)
      {
        encoder.setPosition(1);
        SUB_ACTIVE = 0;
      }
       break;
    default:
        if (pos < 0) {
          pos = 0;
        } else if (pos > 12) {
          pos = 12;
        }
      break;
  }
  }

  if (digitalRead(14) == HIGH) {
    // Button pressed, start or restart the countdown
    start_time = current_time;
    target_time = start_time + std::chrono::seconds(30);
    countdownStarted = true;
    //Serial.println("Countdown started.");
  }

  if (countdownStarted && current_time < target_time) {
    // Calculate remaining time
    std::chrono::duration<double> remaining_seconds = target_time - current_time;

    // Display the remaining time
   // Serial.print("Remaining time: ");
    //Serial.print(remaining_seconds.count());
   // Serial.println(" seconds.");
  } else {
    countdownStarted = false;
    Serial.println("Countdown finished.");
  }
  
  // Kurze Verzögerung, um die Schleife zu verlangsamen (kann je nach Anforderungen angepasst werden)
}
