#include "display.h"


void setup() 
{
 
Serial.begin(115200);

if (! rtc.begin()) {
Serial.println("Couldn't find RTC");
while (1);              
}
 
if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) 
{ 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
}
}


void loop()
{
void HomeBildschirm();


}
