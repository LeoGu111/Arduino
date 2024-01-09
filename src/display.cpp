#include <display.h>


// funktion für die Start up sequenz zur diagnose ob Startup fehlgeschlagen
void display_starting_screen()
{
display.clearDisplay();
display.setTextColor(WHITE);
display.setTextSize(2);
display.drawRect(0, 0, 128, 64, WHITE);
display.display();
delay(500);

display.drawRect(4, 8, 120, 48, WHITE);
display.display();
delay(500);

display.drawRect(8, 16, 112, 32, WHITE);
display.display();
delay(500);

display.drawRect(12, 24, 104, 16, WHITE);
display.display();
delay(500);

}
// funktion für die Start up sequenz
void display_starting_screen_1()
{
display.clearDisplay();
display.setTextColor(WHITE);
display.setTextSize(2);
display.setCursor(32,0);
display.print("Timer");
display.setCursor(24,20);
display.print("Projekt");
display.setCursor(4,40);
display.print("Lucas, Leo");
display.display();
delay(3000);
}
//vollständige Start Sequenz mit RTC Fehlermeldung 
void display_Start_sequenz()
{

//StartBildschirm 1 um zusehen ob die RTC gefunden wurde 
display_starting_screen();
//Startbildschirm RTC wurde erfolglreich gefunden
display_starting_screen_1();

}
// funktion für den Allgm Homebildschirm mit uhrzeit und datum
void HomeBildschirm(){
DateTime now = rtc.now();
display_draw_time(now);
display_draw_date(now);
display.display(); 
}
// funktion um die aktuelle Uhrezeit zu zeichnen
void display_draw_date(DateTime now)
{
display.setTextSize(2);
display.setCursor(0,20);
display.println(now.day(), DEC);
 
display.setTextSize(2);
display.setCursor(25,20);
display.println("-");
 
display.setTextSize(2);
display.setCursor(40,20);
display.println(now.month(), DEC);
 
display.setTextSize(2);
display.setCursor(65,20);
display.println("-");
 
display.setTextSize(2);
display.setCursor(80,20);
display.println(now.year(), DEC);
 
display.setTextSize(2);
display.setCursor(0,40);
display.print(daysOfTheWeek[now.dayOfTheWeek()]);
}
// funktion um das aktuelle datum zu zeichnen
void display_draw_time(DateTime now)
{
display.clearDisplay();
display.setTextSize(2);
display.setCursor(75,0);
display.println(now.second(), DEC);
 
display.setTextSize(2);
display.setCursor(25,0);
display.println(":");
 
display.setTextSize(2);
display.setCursor(65,0);
display.println(":");
 
display.setTextSize(2);
display.setCursor(40,0);
display.println(now.minute(), DEC);
 
display.setTextSize(2);
display.setCursor(0,0);
display.println(now.hour(), DEC);
 
}
// Haupt menue was erscheint nach dem man nach unten scrollt vom homebildschirm
void Menue_1(int X)
{
display.clearDisplay();
display.setTextColor(WHITE);
display.setTextSize(2);
display.setCursor(32,2);
display.print(Menue_eintrag_1);
display.drawRect(0, X, 128, 19, WHITE);
display.setCursor(4,24);
display.print(Menue_eintrag_2);
display.setCursor(16,42);
display.print(Menue_eintrag_3);
display.display();
}
// Timer Menue
void Menue_Timer(double Timer_1, double Timer_2, double Timer_3)
{
display.clearDisplay();
display.setTextColor(WHITE);
display.setTextSize(2);
display.setCursor(center_function(convertFromIndustrialHours(Timer_1),12),2);
display.printf("%d:%d:%d",convertFromIndustrialHours(Timer_1));
display.setCursor(center_function(convertFromIndustrialHours(Timer_2),12),22);
display.printf("%d:%d:%d",convertFromIndustrialHours(Timer_2));
display.setCursor(center_function(convertFromIndustrialHours(Timer_3),12),42);
display.printf("%d:%d:%d",convertFromIndustrialHours(Timer_3));
}
// SubMenue wo die ersten uhrzeiten angezeigt werden /kommt nach dem bestätigen vom menue punkt "timer" im haupt menue
void SubMenue_1_1(int X, float H_1, float H_2, float H_3) //X ist die Positon vom Curser für die auswahl
{
display.clearDisplay();
display.setTextColor(WHITE);
display.setTextSize(2);
//Schreib zentriert die werte für Stunden minuten und sekunden
display.setCursor(center_function(convertFromIndustrialHours(H_1),12),2);
display.printf("%d:%d:%d",convertFromIndustrialHours(H_1));
//Schreib zentriert die werte für Stunden minuten und sekunden
display.setCursor(center_function(convertFromIndustrialHours(H_2),12),22);
display.printf("%d:%d:%d",convertFromIndustrialHours(H_2));
//Schreib zentriert die werte für Stunden minuten und sekunden
display.setCursor(center_function(convertFromIndustrialHours(H_3),12),42);
display.printf("%d:%d:%d",convertFromIndustrialHours(H_3));
//Zeichnet den Curser über die verschiedenen Zeiten
display.drawRect(0, X, 128, 19, WHITE);
display.display();
}
// funktion um die Uhrzeiten zu zentrien X ist die größe de Buchstaben
int center_function(Time industrie, int X)
{
Time convertedTime = industrie;

int digitCount_H = (convertedTime.hours != 0) ? ((int)log10(abs(convertedTime.hours)) + 1) : 1;
int digitCount_M = (convertedTime.minutes != 0) ? ((int)log10(abs(convertedTime.minutes)) + 1) : 1;
int digitCount_S = (convertedTime.seconds != 0) ? ((int)log10(abs(convertedTime.seconds)) + 1) : 1;

//+2 * X wegen den : bei der Zahlen trennung

int versatz_1 = 64 - ((digitCount_H * X + digitCount_M * X + digitCount_S * X + 2 * X)/2);

return abs(versatz_1);
}

void menue_Auswahl()
{
if(SUB_ACTIVE == 0 and SUB_ACTIVE_2 == 0 and Menue_Timer_1 == 0 and SUB_ACTIVE_3 == 0){
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
}

void Menue_Timer_Anzeige()
{
if ((pos == 1 and PIN_SW_PF == 0 and SUB_ACTIVE == 0 and SUB_ACTIVE_2 == 0) or Menue_Timer_1)
{
  Menue_Timer(Timer_1/3600,Timer_2/3600,Timer_3/3600);
  display.display();
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
}

void Menue_Timer_Auswahl()
{
    if ((pos == 2 and PIN_SW_PF == 0 and SUB_ACTIVE_2 == 0 and SUB_ACTIVE_3 == 0 and Menue_Timer_1 == 0) or SUB_ACTIVE == 1){
    switch (pos) {
    case 0:
      SubMenue_1_1(0, floatArray[0], floatArray[1], floatArray[2]);
      Number = 0;
      break;
    case 1:
      SubMenue_1_1(20, floatArray[0], floatArray[1], floatArray[2]);
      Number = 1;
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
      }
      break;
    case 3:
      SubMenue_1_1(0, floatArray[3], floatArray[4], floatArray[5]);
      Number = 3;
      break;
    case 4:
      SubMenue_1_1(20, floatArray[3], floatArray[4], floatArray[5]);
      Number = 4;
      break;
    case 5:
      SubMenue_1_1(40,  floatArray[3], floatArray[4], floatArray[5]);
      Number = 5;
      break;
    case 6:
      SubMenue_1_1(0, floatArray[6], floatArray[7], floatArray[8]);
      Number = 6;
      break;
    case 7:
      SubMenue_1_1(20, floatArray[6], floatArray[7], floatArray[8]);
      Number = 7;
      break;
    case 8:
      SubMenue_1_1(40,floatArray[6], floatArray[7], floatArray[8]);
      Number = 8;
      break;
    case 9:
      SubMenue_1_1(0, floatArray[9], floatArray[10], floatArray[11]);
      Number = 9;
      break;
    case 10:
      SubMenue_1_1(20, floatArray[9], floatArray[10], floatArray[11]);
      Number = 10;
      break;
    case 11:
      SubMenue_1_1(40, floatArray[9], floatArray[10], floatArray[11]);
      Number = 11;
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
 }

void Menue_Timer_Einstellen()
{    
if ((pos == 3 and PIN_SW_PF == 0 and SUB_ACTIVE == 0 and SUB_ACTIVE_3 == 0 and Menue_Timer_1 == 0) or SUB_ACTIVE_2 == 1){
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
}

void speicher_Auswahl()
{
if((SUB_ACTIVE == 1 and SUB_ACTIVE_2 == 0 and Menue_Timer_1 == 0 and PIN_SW_PF == 0) or SUB_ACTIVE_3 == 1){
  SUB_ACTIVE = 0;
  if (pos < 0) 
  {
  pos = -1;
  } 
  else if (pos > 2) 
  {
  pos = 2;
  }
    switch (pos) {
      case 0:
        Menue_Timer(Timer_1/3600, Timer_2/3600, Timer_3/3600);
        display.drawRect(0, 0, 128, 19, WHITE);
        display.display();
        if (PIN_SW_PF == 0 and SUB_ACTIVE_3 == 1)
        {
          Timer_1 = floatArray[Number] * 3600.0;
          SUB_ACTIVE_3 = 0;
          Menue_Timer_1 = 1;
          break;
        }
        SUB_ACTIVE_3 = 1;  
        break;
      case 1:
        Menue_Timer(Timer_1/3600, Timer_2/3600, Timer_3/3600);
        display.drawRect(0, 20, 128, 19, WHITE);
        display.display();
        if (PIN_SW_PF == 0 and SUB_ACTIVE_3 == 1)
        {
          Timer_2 = floatArray[Number] * 3600.0;
          SUB_ACTIVE_3 = 0;
          Menue_Timer_1 = 1;
          break;
        }
        SUB_ACTIVE_3 = 1;  
        break;
      case 2:
        Menue_Timer(Timer_1/3600, Timer_2/3600, Timer_3/3600);
        display.drawRect(0, 40, 128, 19, WHITE);
        display.display();
        if (PIN_SW_PF == 0 and SUB_ACTIVE_3 == 1)
        {
          Timer_3 = floatArray[Number] * 3600.0;
          SUB_ACTIVE_3 = 0;
          Menue_Timer_1 = 1;
          break;
        }
        SUB_ACTIVE_3 = 1;  
        break;
      default:
        break;
}
}
}

void Timer_Einstellen()
{
if((SUB_ACTIVE == 0 and SUB_ACTIVE_2 == 1 and Menue_Timer_1 == 0 and PIN_SW_PF == 0) or SUB_ACTIVE_3 == 1){
while (true)
{
int i = 0;
int H = 0;
int M = 0;
int S = 0;
double Zeit = 0;
if (PIN_SW_PF == 0)
{
  i++;
}
else if (i > 3)
{
  break;
}


switch (i)
{
case 0:
  H = pos;
  break;
case 1:
  M = pos;
  break;
case 2:
  S = pos;
  break;
}

Zeit = Zeit + H * 3600;
Zeit = Zeit + M * 60;
Zeit = Zeit + S;

display.clearDisplay();
display.setCursor(center_function(convertFromIndustrialHours(Zeit),12),22);
display.printf("%d:%d:%d",convertFromIndustrialHours(Zeit));
display.display();
}

floatArray[pos];



}
}




