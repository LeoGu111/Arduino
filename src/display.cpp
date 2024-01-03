#include <display.h>




void HomeBildschirm(){
DateTime now = rtc.now();
display_draw_time(now);
display_draw_date(now);
display.display(); 
}
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
void display_starting_screen()
{
display.clearDisplay();
display.setTextColor(WHITE);
//display.startscrollright(0x00, 0x0F);
display.setTextSize(2);
display.setCursor(20,0);
display.print("Timer");
display.setCursor(20,20);
display.print("Projekt");
display.setCursor(0,40);
display.print("Lucas, Leo");
display.display();
delay(3000);

}
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
void SubMenue_1_1(int X, int H_1, int M_1, int S_1, int H_2, int M_2, int S_2, int H_3, int M_3, int S_3)
{
display.clearDisplay();
display.setTextColor(WHITE);
display.setTextSize(2);

display.setCursor(center_function(H_1,M_1,S_1),2);
display.printf("%d:%d:%d", H_1, M_1, S_1);

display.setCursor(center_function(H_2,M_2,S_2),24);
display.printf("%d:%d:%d", H_2, M_2, S_2);


display.setCursor(center_function(H_3,M_3,S_3),42);
display.printf("%d:%d:%d", H_3, M_3, S_3);

display.drawRect(0, X, 128, 19, WHITE);

display.display();
}
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
