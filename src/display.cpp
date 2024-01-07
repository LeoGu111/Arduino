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
display.display();
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
