#include <display.h>

// funktion für die Start up sequenz zur diagnose ob Startup fehlgeschlagen
void display_starting_screen()
{
display.clearDisplay();
display.setTextColor(WHITE);
display.setTextSize(2);
display.drawRect(0, 64, 128, 19, WHITE);
delay(500);
display.display();
display.drawRect(0, 56, 120, 19, WHITE);
delay(500);
display.display();
display.drawRect(0, 48, 112, 19, WHITE);
delay(500);
display.display();
display.drawRect(0, 40, 114, 19, WHITE);
delay(500);
display.display();
}
// funktion für die Start up sequenz
void display_starting_screen_1()
{
display.clearDisplay();
display.setTextColor(WHITE);
display.setTextSize(2);
display.setCursor(64-2,0);
display.print("Timer");
display.setCursor(64-6,20);
display.print("Projekt");
display.setCursor(64-5,40);
display.print("Lucas, Leo");
display.display();
delay(3000);
}
//vollständige Start Sequenz mit RTC Fehlermeldung 
void display_RTC_Start_sequenz()
{
//Start der Seriellen Kommunikation
Serial.begin(115200);

//StartBildschirm 1 um zusehen ob die RTC gefunden wurde 
display_starting_screen_1();

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

//Startbildschirm RTC wurde erfolglreich gefunden
display_starting_screen();
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
display.setCursor(30,2);
display.print(Menue_eintrag_1);
display.drawRect(0, X, 128, 19, WHITE);
display.setCursor(2,24);
display.print(Menue_eintrag_2);
display.setCursor(12,42);
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
display.setCursor(center_function(H_1,M_1,S_1),2);
display.printf("%d:%d:%d", H_1, M_1, S_1);
//Schreib zentriert die werte für Stunden minuten und sekunden
display.setCursor(center_function(H_2,M_2,S_2),24);
display.printf("%d:%d:%d", H_2, M_2, S_2);
//Schreib zentriert die werte für Stunden minuten und sekunden
display.setCursor(center_function(H_3,M_3,S_3),42);
display.printf("%d:%d:%d", H_3, M_3, S_3);
//Zeichnet den Curser über die verschiedenen Zeiten
display.drawRect(0, X, 128, 19, WHITE);
display.display();
}
// funktion um die Uhrzeiten zu zentrien
int center_function(int H_1,int M_1,int S_1)
{
int digitCount_H = (H_1 != 0) ? ((int)log10(abs(H_1)) + 1) : 1;
int digitCount_M = (M_1 != 0) ? ((int)log10(abs(M_1)) + 1) : 1;
int digitCount_S = (S_1 != 0) ? ((int)log10(abs(S_1)) + 1) : 1;

//+1 wegen den : bei der Zahlen trennung

int versatz_1 = 32 - (digitCount_H + digitCount_M + digitCount_S + 1)/2;
Serial.print("Versatz_1: ");
Serial.println(versatz_1);

return abs(versatz_1);
}
