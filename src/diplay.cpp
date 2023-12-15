#include "display.h"



void loop()
{
HomeBildschirm;
}

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