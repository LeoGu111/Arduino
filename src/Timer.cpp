#include <Timer.h>
Time convertFromIndustrialHours(long double totalSeconds)
{
    Time result;

    // Convert totalSeconds to integer before applying modulus
    int totalSecondsInt = static_cast<int>(totalSeconds);

    result.hours = totalSecondsInt / 3600;          // 1 hour has 3600 seconds
    result.minutes = (totalSecondsInt % 3600) / 60; // Convert remaining seconds to minutes
    result.seconds = totalSecondsInt % 60;          // Remaining seconds
    if (result.hours < 0)
    {
        result.hours = 0;
    }
    else if (result.minutes < 0)
    {
        result.minutes = 0;
    }
    else if (result.seconds < 0)
    {
        result.seconds = 0;
    }

    return result;
}

void Timer_Main()
{
    unsigned long currentMillis = millis(); // Aktuelle Zeit in Millisekunden

    if (Timer_1 > 0)
    {
        Timer_1 = Timer_1 - (long double)(currentMillis - previousMillis) / 1000;
    }
    if (Timer_2 > 0)
    {
        Timer_2 = Timer_2 - (long double)(currentMillis - previousMillis) / 1000;
    }
    if (Timer_3 > 0)
    {
        Timer_3 = Timer_3 - (long double)(currentMillis - previousMillis) / 1000;
    }

    previousMillis = currentMillis;
}
