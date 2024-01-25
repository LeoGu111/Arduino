#include <neoplixel.h>

// vereint die anderen Funktionen
void Neopixel_funtkion()
{
    findshortestTimer();
    updateLEDsBasedOnShortestTimer();
}
// sucht den kürzesten timer
void findshortestTimer()
{
    if (Timer_1 > 0)
    {
        shortestTimer = Timer_1;
    }

    if (Timer_2 > 0 && Timer_2 <= Timer_1)
    {
        shortestTimer = Timer_2;
    }

    if (Timer_3 > 0 && Timer_3 <= (Timer_1 or Timer_2))
    {
        shortestTimer = Timer_3;
    }

    if (Timer_1_1 > 0)
    {
        Neuer_shortest_Timer = Timer_1_1;
    }

    if (Timer_2_1 > 0 && Timer_2_1 <= Neuer_shortest_Timer)
    {
        Neuer_shortest_Timer = Timer_2_1;
    }

    if (Timer_3_1 > 0 && Timer_3_1 <= Neuer_shortest_Timer)
    {
        Neuer_shortest_Timer = Timer_3_1;
    }
}
// updated die leds der Neopixel
void updateLEDsBasedOnShortestTimer()
{
    int ledsToShow = map(shortestTimer, 0, Neuer_shortest_Timer, 0, LED_COUNT);

    for (int i = 0; i < LED_COUNT; i++)
    {
        if (i < ledsToShow)
        {
            strip.setPixelColor(i, strip.Color(0, 20, 0)); // rot für abgelaufene Zeit
        }
        else
        {
            strip.setPixelColor(i, strip.Color(0, 0, 0)); // Aus für verbleibende Zeit
        }
    }

    strip.show();
}
