#include <Timer.h>




Time convertFromIndustrialHours(double long industrialHours) 
{
    int hours = static_cast<int>(industrialHours); // Extrahiere die ganzen Stunden
    double fractionalPart = industrialHours - hours; // Der Dezimalteil entspricht den Minuten und Sekunden

    int minutes = static_cast<int>(fractionalPart * 60); // Umwandlung des Dezimalteils in Minuten
    double fractionalMinutes = (fractionalPart * 60) - minutes; // Der Dezimalteil entspricht den Sekunden
    //if (static_cast<double>(fractionalMinutes * 60) > 59)
    //{
    //static_cast<double>(fractionalMinutes * 60) + 1;
    //}
    //else
    //{
    int seconds = static_cast<double>(fractionalMinutes * 60); // Umwandlung des Dezimalteils in Sekunden
    //}

    Time result { hours, minutes, seconds };
    return result;
}

void Timer_Main()
{
unsigned long currentMillis = millis(); // Aktuelle Zeit in Millisekunden

if (Timer_1 > 0)
{
Timer_1 = Timer_1 - (float)(currentMillis - previousMillis)/1000;
}
if (Timer_2 > 0)
{
Timer_2 = Timer_2 - (float)(currentMillis - previousMillis)/1000;
}
if (Timer_3 > 0)
{
Timer_3 = Timer_3 - (float)(currentMillis - previousMillis)/1000;
}

previousMillis = currentMillis;
}
