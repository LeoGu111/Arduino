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
void display_RTC_Start_sequenz()
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
// SubMenue wo die ersten uhrzeiten angezeigt werden /kommt nach dem bestätigen vom menue punkt "timer" im haupt menue
void SubMenue_1_1(int X, int H_1, int M_1, int S_1, int H_2, int M_2, int S_2, int H_3, int M_3, int S_3) //X ist die Positon vom Curser für die auswahl
{
display.clearDisplay();
display.setTextColor(WHITE);
display.setTextSize(2);
//Schreib zentriert die werte für Stunden minuten und sekunden
display.setCursor(center_function(H_1,M_1,S_1,12),2);
display.printf("%d:%d:%d", H_1, M_1, S_1);
//Schreib zentriert die werte für Stunden minuten und sekunden
display.setCursor(center_function(H_2,M_2,S_2,12),24);
display.printf("%d:%d:%d", H_2, M_2, S_2);
//Schreib zentriert die werte für Stunden minuten und sekunden
display.setCursor(center_function(H_3,M_3,S_3,12),42);
display.printf("%d:%d:%d", H_3, M_3, S_3);
//Zeichnet den Curser über die verschiedenen Zeiten
display.drawRect(0, X, 128, 19, WHITE);
display.display();
}
// funktion um die Uhrzeiten zu zentrien X ist die größe de Buchstaben
int center_function(int H_1,int M_1,int S_1, int X)
{
int digitCount_H = (H_1 != 0) ? ((int)log10(abs(H_1)) + 1) : 1;
int digitCount_M = (M_1 != 0) ? ((int)log10(abs(M_1)) + 1) : 1;
int digitCount_S = (S_1 != 0) ? ((int)log10(abs(S_1)) + 1) : 1;

//+1 wegen den : bei der Zahlen trennung

int versatz_1 = 64 - ((digitCount_H * X + digitCount_M * X + digitCount_S * X + 2 * X)/2);
Serial.print("Versatz_1: ");
Serial.println(versatz_1);

return abs(versatz_1);
}
